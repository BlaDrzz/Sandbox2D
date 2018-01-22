#pragma once

struct Graphics
{
	Sandbox2D* _engineRef = nullptr;
	Cache*		_cache = nullptr;
	
	// SDL speficic
	SDL_Window*		_window = nullptr;
	SDL_Renderer*	_renderer = nullptr;

	Pixel	_screenDimensions;
	Pixel	_offset					= { 0, 0 };
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
		_screenDimensions = settings.windowSize;

		// Create _window
		_window = SDL_CreateWindow(
			settings.windowTitle.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			_screenDimensions.x,
			_screenDimensions.y,
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

	void setColor(RGBA color)
	{
		_currentDrawingColor = color;

		SDL_SetRenderDrawColor(_renderer,
			_currentDrawingColor.r,
			_currentDrawingColor.g,
			_currentDrawingColor.b,
			_currentDrawingColor.a
		);
	}

	// drawRect overloads
	void drawRect(bool fillRect, Rect<int> rect) const
	{
		auto convertedRect = ToSDL(rect);

		if (fillRect) SDL_RenderFillRect(_renderer, &convertedRect);
		else SDL_RenderDrawRect(_renderer, &convertedRect);
	}
	
	void drawRect(bool fillRect, int x, int y, int xx, int yy) const
	{
		drawRect(fillRect, { x, y, xx, yy });
	}
	void drawRect(bool fillRect, Pixel p1, Pixel p2) const
	{
		drawRect(fillRect, { p1, p2 });
	}
	
	// drawString overloads + helper functions
	SDL_Surface* createTextSurface(std::string s) const
	{
		SDL_Color foreground = {
			_currentDrawingColor.r,
			_currentDrawingColor.g,
			_currentDrawingColor.b,
			_currentDrawingColor.a
		};

		auto convertedFont = _currentFont == ""
			? _cache->fntCache.findByName(_defaultFont)->_TTFfont
			: _cache->fntCache.findByName(_currentFont)->_TTFfont;

		return TTF_RenderText_Blended(convertedFont, s.c_str(), foreground);
	}

	Pixel calculateTextSize(std::string s) const
	{
		SDL_Surface* textSurface = createTextSurface(s);
		Pixel size = { textSurface->w, textSurface->h };

		SDL_FreeSurface(textSurface);

		return size;
	}

	void drawString(std::string string, Rect<int> srcRect, Rect<int> destRect) const
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
				destRect.x.x,
				destRect.x.y,
				textSurface->w + destRect.x.x,
				textSurface->h + destRect.x.y
			};
		else destinationRect = sourceRect;
	
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
	
	void drawString(std::string str, int x, int y) const
	{
		drawString(str, { 0, 0, -1, -1 }, { x, y, -1, -1 });
	}
	void drawString(std::string s, Pixel p) const
	{
		drawString(s, p.x, p.y);
	}
	
	// drawLine overloads
	void drawLine(int x, int y, int xx, int yy) const
	{
		SDL_RenderDrawLine(_renderer, x, y, xx, yy);
	}
	
	void drawLine(Line<int> l) const
	{
		drawLine(l.x.x, l.x.y, l.y.x, l.y.y);
	}
	void drawLine(Pixel p1, Pixel p2) const
	{
		drawLine(MakeLine(p1, p2));
	}
	
	// drawBitmap overloads
	void drawBitmap(Bitmap* bmp, Rect<int> sourceRect, Rect<int> destinationRect) const
	{
		// Create temporary texture and create from _bitmap _surface
		SDL_Texture* texture;
		auto bitmapSurface = bmp->_surface;
		texture = SDL_CreateTextureFromSurface(_renderer, bitmapSurface);
		if (texture == nullptr)
		{
			printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
			return;
		}

		auto sourceSDLRect = ToSDL(sourceRect);
		auto destinationSDLRect = ToSDL(destinationRect);

		// Render the new texture on top of the existing ones and delete temporary texture
		SDL_RenderCopy(_renderer, texture,
			&sourceSDLRect,
			&destinationSDLRect);
		SDL_DestroyTexture(texture);
	}
	
	void drawBitmap(Bitmap* bmp, int x, int y) const
	{
		Rect<int> sourceRect = { 0, 0, bmp->_surface->w, bmp->_surface->h };
		Rect<int> destinationRect = { x, y, bmp->_surface->w + x, bmp->_surface->h + y };

		drawBitmap(bmp, sourceRect, destinationRect);
	}

	void drawBitmap(Bitmap* bmp, Pixel p) const
	{
		drawBitmap(bmp, p.x, p.y);
	}
};