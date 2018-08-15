#pragma once

/**
* \brief Represents the ViewPort
*/
struct ViewPort
{
	/**
	* \brief A Pixel
	*/
	Pixel position = { 0, 0 };

	/**
	* \brief An angle
	*/
	double angle = 0;
};

/**
* \brief Handles Graphics generation
*/
class Graphics
{
public:	
	/**
	* \brief A viewport
	*/
	ViewPort viewPort;
	
	/**
	* \brief Background drawing color
	*/
	RGBA	backgroundDrawingColor	= { 255, 255, 255, 255 };

	/**
	* \brief Current drawing color
	*/
	RGBA	currentDrawingColor	= { 0, 0, 0, 255 };

	/**
	* \brief Constructor
	* @param settings: reference to the game settings
	*/
	Graphics(GameSettings &settings);

	/**
	* \brief Destructor
	*/
	~Graphics();

	// C++11 make class non-copyable
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	
	/**
	* \brief Render all graphics
	* @param game: pointer to GameState
	*/
	void renderAll(GameState* game);

	/**
	* \brief Set a color
	* @param color: color RGBA values from 0 to 255
	*/
	void setColor(RGBA color);

	/**
	* \brief Draw a rectangle
	* @param fillRect: boolean
	* @param rect: reference to a rect
	*/
	void drawRect(bool fillRect, const Rect<int> &rect) const;

	/**
	* \brief Draw a rectangle
	* @param fillRect: boolean
	* @param p1: first pixel
	* @param p2: second pixel
	*/
	void drawRect(bool fillRect, Pixel p1, Pixel p2) const;
	
	/**
	* \brief Creates a text surface (helper function)
	* @param text: a string
	* @param font: pointer to a font (default = nullptr)
	* @return an SDL_Surface
	*/
	SDL_Surface* createTextSurface(std::string text, Font* font = nullptr) const;
	
	/**
	* \brief Calculates the size of the text (helper function)
	* @param text: a string
	* @param font: pointer to a font (default = nullptr)
	* @return A pixel
	*/
	Pixel calculateTextSize(std::string text, Font* font = nullptr) const;

	/**
	* \brief Draw a string
	* @param string: a string
	* @param srcRect: a source rect
	* @param destRect: a destination rect
	* @param font: pointer to a font (default = nullptr)
	*/
	void drawString(std::string string, Rect<int> srcRect, Rect<int> destRect, Font* font = nullptr) const;
	
	/**
	* \brief Draw a string
	* @param string: a string
	* @param p: a Pixel
	* @param font: pointer to a font (default = nullptr)
	*/
	void drawString(std::string string, Pixel p, Font* font = nullptr) const;
	
	/**
	* \brief Draw a Line
	* @param line: reference to a line
	*/
	void drawLine(const Line<int> &line) const;

	/**
	* \brief Draw a Line
	* @param p1: first Pixel
	* @param p2: second Pixel
	*/
	void drawLine(Pixel p1, Pixel p2) const;
	
	/**
	* \brief Draw a bitmap
	* @param bmp: pointer to a bitmap
	* @param sourceRect: reference to the source rect
	* @param destinationRect: reference to the destination rect
	* @param angle: a double (default = 0)
	* @param center: a Pixel (default = {0,0})
	* @param flip: SDL_RendererFlip (default = SDL_FLIP_NONE)
	*/
	void drawBitmap(Bitmap* bmp, const Rect<int> &sourceRect, const Rect<int> &destinationRect,
		double angle = 0, Pixel center = { 0, 0 }, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	
	/**
	* \brief Draw a bitmap
	* @param bmp: pointer to a bitmap
	* @param position: a Pixel 
	* @param angle: a double (default = 0)
	* @param center: a Pixel (default = {0,0})
	*/
	void drawBitmap(Bitmap* bmp, Pixel position, double angle = 0, Pixel center = { 0, 0 }) const;

	/**
	* \brief Gets the size of the window
	* @return _windowSize
	*/
	Pixel getWindowSize() const { return _windowSize; }

private:
	/**
	* \brief A pointer to the window
	*/
	SDL_Window *	_window = nullptr;

	/**
	* \brief A pointer to the renderer
	*/
	SDL_Renderer*	_renderer = nullptr;

	// Engine specific
	/**
	* \brief A pixel as size of the window
	*/
	Pixel	_windowSize = { 0, 0 };

	/**
	* \brief A pointer to a default font
	*/
	Font*	_defaultFont = nullptr;
};