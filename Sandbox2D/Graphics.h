#pragma once

struct ViewPort
{
	Pixel position = { 0, 0 };
	double angle = 0;
};

// TODO: Add documentation
class Graphics
{
public:	
	ViewPort _viewPort;
	
	RGBA	_backgroundDrawingColor	= { 255, 255, 255, 255 };
	RGBA	_currentDrawingColor	= { 0, 0, 0, 255 };

	// Con-/Destructor
	Graphics(GameSettings &settings);
	~Graphics();

	// C++11 make class non-copyable
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	
	void renderAll(GameState* game);

	//! @param color RGBA values from 0 to 255.
	void setColor(RGBA color);

	// drawRect overloads
	void drawRect(bool fillRect, const Rect<int> &rect) const;
	void drawRect(bool fillRect, Pixel p1, Pixel p2) const;
	
	// drawString overloads + helper functions
	SDL_Surface* createTextSurface(std::string text, Font* font = nullptr) const;
	Pixel calculateTextSize(std::string text, Font* font = nullptr) const;

	void drawString(std::string string, Rect<int> srcRect, Rect<int> destRect, Font* font = nullptr) const;
	void drawString(std::string string, Pixel p, Font* font = nullptr) const;
	
	// drawLine overloads
	void drawLine(const Line<int> &line) const;
	void drawLine(Pixel p1, Pixel p2) const;
	
	// drawBitmap overloads
	void drawBitmap(Bitmap* bmp, const Rect<int> &sourceRect, const Rect<int> &destinationRect,
		double angle = 0, Pixel center = { 0, 0 }, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void drawBitmap(Bitmap* bmp, Pixel position, double angle = 0, Pixel center = { 0, 0 }) const;

	// Getters/setters
	Pixel getWindowSize() const { return _windowSize; }

private:
	// SDL speficic
	SDL_Window *	_window = nullptr;
	SDL_Renderer*	_renderer = nullptr;

	// Engine specific
	Pixel	_windowSize = { 0, 0 };
	Font*	_defaultFont = nullptr;
};