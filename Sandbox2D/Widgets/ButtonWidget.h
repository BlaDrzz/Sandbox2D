#pragma once

#define S2D (Sandbox2D::GetSingleton())

/**
* \brief Represents a buttonwidget (Subclass of Widget)
*/
struct ButtonWidget : Widget
{
	Pixel _size = { 0, 0 };
	RGBA _backColor = { 0, 0, 0, 0 };
	RGBA _fontColor = { 0, 0, 0, 255 };
	std::string _text = "";
	Rect<int> _textPadding = { 5, 5, 5, 5 };

	/**
	* \brief Constructor
	* @param position: a Pixel
	*/
	ButtonWidget(Pixel position)
	{
		ButtonWidget(position, "");
	}

	/**
	* \brief Constructor
	* @param position: a Pixel
	* @param text: a string
	*/
	ButtonWidget(Pixel position, std::string text) : _text(text)
	{
		// Set parent position
		this->_position = position;

		// Set some defaults
		_backColor = RGBA{ 230,230,230,255 };
	}

	/**
	* \brief Destructor
	*/
	~ButtonWidget() {}

	/**
	* \brief Tick function
	* @param deltaTime: a double
	*/
	void tick(double deltaTime) override {}

	/**
	* \brief Draw function
	* @param g: pointer to a Graphics object
	*/
	void draw(Graphics* g) override
	{
		if (_hidden) return;

		// Store initial state
		const RGBA previousColor = g->currentDrawingColor;

		const Pixel pointA = absolutePosition();
		const Pixel pointB = pointA + _size;

		// Resize text if needed
		if (_size.x == 0 || _size.y == 0) resizeToText(g);

		const Pixel textPosition = { pointA.x + _textPadding.x.x, pointA.y + _textPadding.x.y };

		// Draw Background
		g->setColor(_backColor);
		g->drawRect(true, pointA, pointB);

		// Draw Text
		g->setColor(_fontColor);
		g->drawString(_text, textPosition);

		// Make sure to reset back to initial state
		g->setColor(previousColor);
	}

	/**
	* \brief Resize to text
	* @param g: pointer to a Graphics object
	*/
	void resizeToText(Graphics* g)
	{
		const Pixel textSize = g->calculateTextSize(_text);

		_size = {
			_textPadding.x.x + textSize.x + _textPadding.y.x,
			_textPadding.x.y + textSize.y + _textPadding.y.y
		};
	}

	/**
	* \brief Check if pressed
	* @return A boolean
	*/
	bool isPressed() const
	{
		const auto mousePos = S2D->inputManager->getMousePos();
		const Rect<int> buttonRect = { absolutePosition(), absolutePosition() + _size };

		return Contains(buttonRect, mousePos) && S2D->inputManager->isMouseButtonReleased(SDL_BUTTON_LEFT);
	}
};