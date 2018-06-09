#include "../stdafx.h"

Graphics::Graphics(GameSettings &settings)
{
	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return;
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
		return;
	}

	// Start SDL init threads
	auto fRenderer = std::async(SDL_CreateRenderer, _window, -1, SDL_RENDERER_ACCELERATED);

	const auto imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
	auto fImg = std::async(IMG_Init, IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);

	auto fTtf = std::async(TTF_Init);


	//_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	_renderer = fRenderer.get();

	if (_renderer == nullptr)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

	// Initialise image loading
	// Initialise PNG loading
	if (!(fImg.get() & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return;
	}

	// Initialise TTF
	if (fTtf.get() < 0)
	{
		printf("SDL_TTF could not initialize! SDL_TTF Error: %s\n", TTF_GetError());
		return;
	}

	// Set default font
	_defaultFont = new Font("Resources/arial.ttf", 12);

	LogInfo("Graphics initialised successfully!");
}

Graphics::~Graphics()
{
	// Self cleanup
	delete _defaultFont;

	// Close SDL
	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;
	SDL_DestroyWindow(_window);
	_window = nullptr;
}

void Graphics::renderAll(GameState* game)
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

void Graphics::setColor(const RGBA color)
{
	_currentDrawingColor = color;

	SDL_SetRenderDrawColor(_renderer,
		clamp(int(_currentDrawingColor.r), 0, 255),
		clamp(int(_currentDrawingColor.g), 0, 255),
		clamp(int(_currentDrawingColor.b), 0, 255),
		clamp(int(_currentDrawingColor.a), 0, 255)
	);
}

void Graphics::drawRect(const bool fillRect, const Rect<int>& rect) const
{
	auto convertedRect = ToSDL(rect - Rect<int>{_viewPort.position, _viewPort.position});

	if (fillRect) SDL_RenderFillRect(_renderer, &convertedRect);
	else SDL_RenderDrawRect(_renderer, &convertedRect);
}

void Graphics::drawRect(const bool fillRect, const Pixel p1, const Pixel p2) const
{
	drawRect(fillRect, { p1, p2 });
}

SDL_Surface* Graphics::createTextSurface(const std::string text, Font* font) const
{
	const SDL_Color foreground = {
		_currentDrawingColor.r,
		_currentDrawingColor.g,
		_currentDrawingColor.b,
		_currentDrawingColor.a
	};

	return TTF_RenderText_Blended(
		font == nullptr ? _defaultFont->TTFfont : font->TTFfont, 
		text.c_str(), foreground);
}

Pixel Graphics::calculateTextSize(const std::string text, Font* font) const
{
	const auto textSurface = createTextSurface(text, font);
	const Pixel size = { textSurface->w, textSurface->h };

	SDL_FreeSurface(textSurface);

	return size;
}

void Graphics::drawString(const std::string string, const Rect<int> srcRect, const Rect<int> destRect, Font* font) const
{
	// Create surface from string
	const auto textSurface = createTextSurface(string, font);
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
	if (destRect.y.x == -1 && destRect.y.y == -1)
		destinationRect = {
		destRect.x.x - _viewPort.position.x,
		destRect.x.y - _viewPort.position.y,
		textSurface->w - _viewPort.position.x + destRect.x.x,
		textSurface->h - _viewPort.position.y + destRect.x.y
	};
	else destinationRect = sourceRect - Rect<int>{_viewPort.position, _viewPort.position};

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

void Graphics::drawString(const std::string string, const Pixel p, Font* font) const
{
	drawString(string, { 0, 0, -1, -1 }, { p.x, p.y, -1, -1 }, font);
}

void Graphics::drawLine(const Line<int>& line) const
{
	SDL_RenderDrawLine(_renderer,
		line.x.x - _viewPort.position.x,
		line.x.y - _viewPort.position.y,
		line.y.x - _viewPort.position.x,
		line.y.y - _viewPort.position.y);
}

void Graphics::drawLine(const Pixel p1, const Pixel p2) const
{
	drawLine(MakeLine(p1, p2));
}

void Graphics::drawBitmap(Bitmap* bmp, const Rect<int>& sourceRect, const Rect<int>& destinationRect,
	const double angle, const Pixel center, const SDL_RendererFlip flip) const
{
	const auto bitmapSurface = bmp->_surface;
	const auto texture = SDL_CreateTextureFromSurface(_renderer, bitmapSurface);
	if (texture == nullptr)
	{
		printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
		return;
	}

	auto sourceSDLRect = ToSDL(sourceRect);
	auto destinationSDLRect = ToSDL(destinationRect - Rect<int>{_viewPort.position, _viewPort.position});

	// Render the new texture on top of the existing ones and delete temporary texture
	SDL_RenderCopyEx(
		_renderer,
		texture,
		&sourceSDLRect,
		&destinationSDLRect,
		angle,
		center == Pixel{ NULL, NULL } ? nullptr : new SDL_Point(ToSDL(center)),
		flip
	);
	SDL_DestroyTexture(texture);
}

void Graphics::drawBitmap(Bitmap* bmp, const Pixel position, const double angle, const Pixel center) const
{
	const Rect<int> sourceRect = { { 0, 0 },{ bmp->_surface->w, bmp->_surface->h } };
	const Rect<int> destinationRect = { position,{ bmp->_surface->w + position.x, bmp->_surface->h + position.y } };

	drawBitmap(bmp, sourceRect, destinationRect, angle, center);
}
