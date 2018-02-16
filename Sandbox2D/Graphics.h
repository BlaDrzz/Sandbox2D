#pragma once

struct ViewPort
{
	Pixel _position = { 0, 0 };
	double _angle = 0;

	ViewPort() {}
	ViewPort(const Pixel pos, const double angle) : _position(pos), _angle(angle) {}
	
	void defaults()
	{
		_position = { 0, 0 };
		_angle = 0;
	}
};

struct Graphics
{
	Sandbox2D* _engineRef = nullptr;
	Cache*		_cache = nullptr;
	
	// SDL speficic
	SDL_Window*		_window = nullptr;
	SDL_Renderer*	_renderer = nullptr;

	ViewPort _viewPort;
	Pixel	_windowSize;
	RGBA	_backgroundDrawingColor	= { 255, 255, 255, 255 };
	RGBA	_currentDrawingColor	= { 0, 0, 0, 255 };

	std::string	_defaultFont = "defaultFont";
	std::string	_currentFont = "";

	bool init(Sandbox2D* LVN_enginePtr, GameSettings &settings, Cache* cache)
	{
		_engineRef = LVN_enginePtr;
		_cache = cache;

		// Initialise SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			return false;
		}

		// Store _window _size if needed by user
		_windowSize = settings._windowSize;

		// Create _window
		_window = SDL_CreateWindow(
			settings._windowTitle.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			_windowSize.x,
			_windowSize.y,
			SDL_WINDOW_SHOWN
		);

		if (_window == nullptr)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}

		// Start SDL init threads
		auto fRenderer = std::async(SDL_CreateRenderer, _window, -1, SDL_RENDERER_ACCELERATED);
		
		const auto imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
		auto fImg = std::async(IMG_Init, IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF);

		auto fTtf = std::async(TTF_Init);


		//_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
		_renderer = fRenderer.get();

		if (_renderer == nullptr)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
		
		// Initialise image loading
		// Initialise PNG loading
		if (!(fImg.get() & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			return false;
		}

		// Initialise TTF
		if (fTtf.get() < 0)
		{
			printf("SDL_TTF could not initialize! SDL_TTF Error: %s\n", TTF_GetError());
			return false;
		}
		
		// Set default font
		cache->fntCache.push(
			_defaultFont,
			cache->fntCache.CreateCachableFont("Resources/arial.ttf", 12)
		);
		
		LogInfo("Graphics initialised successfully!");

		return true;
	}

	void cleanup()
	{
		// Close SDL
		SDL_DestroyRenderer(_renderer);
		_renderer = nullptr;
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}

	void renderAll(GameState* game)
	{
		// Reset the _renderer
		SDL_RenderClear(_renderer);

		setColor(_currentDrawingColor);

		// User defined draw functions
		game->statePaint(this);

		// Set background color
		SDL_SetRenderDrawColor(_renderer,
			_backgroundDrawingColor.r,
			_backgroundDrawingColor.g,
			_backgroundDrawingColor.b,
			_backgroundDrawingColor.a
		);

		// Render the final screen
		SDL_RenderPresent(_renderer);
	}

	//! @param color RGBA values from 0 to 255.
	void setColor(RGBA color)
	{
		_currentDrawingColor = color;

		SDL_SetRenderDrawColor(_renderer,
			CLAMP(_currentDrawingColor.r, 0, 255),
			CLAMP(_currentDrawingColor.g, 0, 255),
			CLAMP(_currentDrawingColor.b, 0, 255),
			CLAMP(_currentDrawingColor.a, 0, 255)
		);
	}

	// drawRect overloads
	void drawRect(const bool fillRect, const Rect<int> &rect) const
	{
		auto convertedRect = ToSDL(rect - Rect<int>{_viewPort._position, _viewPort._position});

		if (fillRect) SDL_RenderFillRect(_renderer, &convertedRect);
		else SDL_RenderDrawRect(_renderer, &convertedRect);
	}
	
	void drawRect(const bool fillRect, const Pixel p1, const Pixel p2) const
	{
		drawRect(fillRect, { p1, p2 });
	}
	
	// drawString overloads + helper functions
	SDL_Surface* createTextSurface(const std::string s) const
	{
		const SDL_Color foreground = {
			_currentDrawingColor.r,
			_currentDrawingColor.g,
			_currentDrawingColor.b,
			_currentDrawingColor.a
		};

		const auto convertedFont = _currentFont == ""
			? _cache->fntCache.findByName(_defaultFont)->_TTFfont
			: _cache->fntCache.findByName(_currentFont)->_TTFfont;

		return TTF_RenderText_Blended(convertedFont, s.c_str(), foreground);
	}

	Pixel calculateTextSize(const std::string s) const
	{
		SDL_Surface* textSurface = createTextSurface(s);
		const Pixel size = { textSurface->w, textSurface->h };

		SDL_FreeSurface(textSurface);

		return size;
	}

	void drawString(const std::string string, const Rect<int> srcRect, const Rect<int> destRect) const
	{
		// Create surface from string
		const auto textSurface = createTextSurface(string);
		const auto texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
		if (texture == nullptr)
		{
			printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
			return;
		}
	
		// Create source rect
		Rect<int> sourceRect;

		if (srcRect.y.x == -1 && srcRect.y.y == -1)
			sourceRect = {
				0,
				0,
				textSurface->w,
				textSurface->h 
			};
		else sourceRect = srcRect;
		
		// Create destination rect
		Rect<int> destinationRect;
		if (destRect.y.x == -1 && destRect.y.x == -1)
			destinationRect = {
				destRect.x.x - _viewPort._position.x,
				destRect.x.y - _viewPort._position.y,
				textSurface->w - _viewPort._position.x + destRect.x.x,
				textSurface->h - _viewPort._position.y + destRect.x.y
			};
		else destinationRect = sourceRect - Rect<int>{_viewPort._position, _viewPort._position};
	
		auto sourceSDLRect = ToSDL(sourceRect);
		auto destinationSDLRect = ToSDL(destinationRect);

		// Render the new texture on top of the existing ones and delete temporary texture
		SDL_RenderCopy(_renderer, texture,
			&sourceSDLRect,
			&destinationSDLRect);
	
		// cleanup
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(textSurface);
	}
	
	void drawString(const std::string string, const Pixel p) const
	{
		drawString(string, { 0, 0, -1, -1 }, { p.x, p.y, -1, -1 });
	}
	
	// drawLine overloads
	void drawLine(const Line<int> &line) const
	{
		SDL_RenderDrawLine(_renderer, 
			line.x.x - _viewPort._position.x, 
			line.x.y - _viewPort._position.y,
			line.y.x - _viewPort._position.x,
			line.y.y - _viewPort._position.y);
	}
	void drawLine(const Pixel p1, const Pixel p2) const
	{
		drawLine(MakeLine(p1, p2));
	}
	
	// drawBitmap overloads
	void drawBitmap(Bitmap* bmp, const Rect<int> &sourceRect, const Rect<int> &destinationRect, 
		const double angle = 0, const Pixel center = { NULL, NULL }, const SDL_RendererFlip flip = SDL_FLIP_NONE) const
	{
		const auto bitmapSurface = bmp->_surface;
		const auto texture = SDL_CreateTextureFromSurface(_renderer, bitmapSurface);
		if (texture == nullptr)
		{
			printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
			return;
		}

		auto sourceSDLRect = ToSDL(sourceRect);
		auto destinationSDLRect = ToSDL(destinationRect - Rect<int>{_viewPort._position, _viewPort._position});

		// Render the new texture on top of the existing ones and delete temporary texture
		SDL_RenderCopyEx(
			_renderer, 
			texture,
			&sourceSDLRect,
			&destinationSDLRect,
			angle,
			center == Pixel{ NULL, NULL } ? NULL : new SDL_Point(ToSDL(center)),
			flip
		);
		SDL_DestroyTexture(texture);
	}

	void drawBitmap(Bitmap* bmp, const Pixel position, const double angle = 0, const Pixel center = { NULL, NULL }, const SDL_RendererFlip flip = SDL_FLIP_NONE) const
	{
		const Rect<int> sourceRect = { { 0, 0 }, { bmp->_surface->w, bmp->_surface->h } };
		const Rect<int> destinationRect = { position, { bmp->_surface->w + position.x, bmp->_surface->h + position.y } };


		drawBitmap(bmp, sourceRect, destinationRect, angle, center);
	}
};