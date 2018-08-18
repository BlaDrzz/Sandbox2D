#pragma once

#define S2D (Sandbox2D::GetSingleton())

/**
* \brief Represents a buttonwidget (Subclass of Widget)
*/
struct ButtonWidget : Widget
{
	Pixel size = { 0, 0 };
	RGBA backColor = { 0, 0, 0, 0 };
	RGBA fontColor = { 0, 0, 0, 255 };
	std::string text = "";
	Rect<int> textPadding = { 5, 5, 5, 5 };

	/**
	* \brief Constructor
	* @param position: a Pixel
	*/
	ButtonWidget(const Pixel position)
	{
		ButtonWidget(position, "");
	}

	/**
	* \brief Constructor
	* @param position: a Pixel
	* @param text: a string
	*/
	ButtonWidget(const Pixel position, const std::string text) : text(text)
	{
		// Set parent position
		this->position = position;

		// Set some defaults
		backColor = RGBA{ 230,230,230,255 };
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
		if (hidden) return;

		// Store initial state
		const auto previousColor = g->currentDrawingColor;

		const auto pointA = absolutePosition();
		const auto pointB = pointA + size;

		// Resize text if needed
		if (size.x == 0 || size.y == 0) resizeToText(g);

		const Pixel textPosition = { pointA.x + textPadding.x.x, pointA.y + textPadding.x.y };

		// Draw Background
		g->setColor(backColor);
		g->drawRect(true, pointA, pointB);

		// Draw Text
		g->setColor(fontColor);
		g->drawString(text, textPosition);

		// Make sure to reset back to initial state
		g->setColor(previousColor);
	}

	/**
	* \brief Resize to text
	* @param g: pointer to a Graphics object
	*/
	void resizeToText(Graphics* g)
	{
		const auto textSize = g->calculateTextSize(text);

		size = {
			textPadding.x.x + textSize.x + textPadding.y.x,
			textPadding.x.y + textSize.y + textPadding.y.y
		};
	}

	/**
	* \brief Check if pressed
	* @return A boolean
	*/
	bool isPressed() const
	{
		const auto mousePos = S2D->inputManager->getMousePos();
		const Rect<int> buttonRect = { absolutePosition(), absolutePosition() + size };

		return Contains(buttonRect, mousePos) && S2D->inputManager->isMouseButtonReleased(SDL_BUTTON_LEFT);
	}
};