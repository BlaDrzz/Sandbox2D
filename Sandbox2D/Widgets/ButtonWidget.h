#pragma once

#define S2D (Sandbox2D::GetSingleton())

struct ButtonWidget : Widget
{
	Pixel _size = { 0, 0 };
	RGBA _backColor = { 0, 0, 0, 0 };
	RGBA _fontColor = { 0, 0, 0, 255 };
	std::string _text = "";
	Rect<int> _textPadding = { 5, 5, 5, 5 };

	ButtonWidget(Pixel position)
	{
		ButtonWidget(position, "");
	}
	ButtonWidget(Pixel position, std::string text) : _text(text)
	{
		// Set parent position
		this->_position = position;

		// Set some defaults
		_backColor = RGBA{ 230,230,230,255 };
	}
	~ButtonWidget() {}

	void tick(double deltaTime) override {}

	void draw(Graphics* g) override
	{
		if (_hidden) return;

		// Store initial state
		const RGBA previousColor = g->_currentDrawingColor;

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

	void resizeToText(Graphics* g)
	{
		const Pixel textSize = g->calculateTextSize(_text);

		_size = {
			_textPadding.x.x + textSize.x + _textPadding.y.x,
			_textPadding.x.y + textSize.y + _textPadding.y.y
		};
	}

	bool isPressed() const
	{
		const auto mousePos = S2D->_inputManager->getMousePos();
		const Rect<int> buttonRect = { absolutePosition(), absolutePosition() + _size };

		return Contains(buttonRect, mousePos) && S2D->_inputManager->isMouseButtonReleased(SDL_BUTTON_LEFT);
	}
};