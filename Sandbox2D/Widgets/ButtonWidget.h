#pragma once

#define S2D (Sandbox2D::GetSingleton())

struct ButtonWidget : Widget
{
	Pixel _size = { 0, 0 };
	RGBA _backColor = { 0, 0, 0, 0 };
	RGBA _fontColor = { 0, 0, 0, 255 };
	std::string _text = "";
	Rect<int> _textPadding = { 5, 5, 5, 5 };
	Observer *_ob = new Observer;

	ButtonWidget(Pixel position)
	{
		_position = position;

		On(S2D->_mouseObserver, "mousedown", [this](Event e)
		{
			// Find out if mouse is in button
			auto mouse = S2D->_inputManager->GetMousePos();
		
			Rect<int> selfRect = { absolutePosition(), absolutePosition() + _size };
			

			std::cout << "observer: " << _ob << " this: " << this << std::endl;

			if (Contains(selfRect, mouse))
				Emit(_ob, Event{ "clicked", Any::Any(mouse) }, [](Any::Any any)
			{
				any.free<Pixel>();
			});
		});
	}
	ButtonWidget(Pixel position, std::string text) : _text(text)
	{
		_position = position;
	}
	~ButtonWidget()
	{
		delete _ob;
		_ob = nullptr;
	}

	void tick(double deltaTime) override {}

	void draw() override
	{
		if (_hidden) return;

		// Store initial state
		const RGBA previousColor = S2D->_graphics->_currentDrawingColor;

		const Pixel pointA = absolutePosition();
		const Pixel pointB = pointA + _size;

		// Resize text if needed
		if (_size.x == 0 || _size.y == 0) resizeToText();

		const Pixel textPosition = { pointA.x + _textPadding.x.x, pointA.y + _textPadding.x.y };

		// Draw Background
		S2D->_graphics->setColor(_backColor);
		S2D->_graphics->drawRect(true, pointA, pointB);

		// Draw Text
		S2D->_graphics->setColor(_fontColor);
		S2D->_graphics->drawString(_text, textPosition);

		// Make sure to reset back to initial state
		S2D->_graphics->setColor(previousColor);
	}

	void resizeToText()
	{
		const Pixel textSize = S2D->_graphics->calculateTextSize(_text);

		_size = {
			_textPadding.x.x + textSize.x + _textPadding.y.x,
			_textPadding.x.y + textSize.y + _textPadding.y.y
		};
	}

	bool isPressed() const
	{
		const auto mousePos = S2D->_inputManager->GetMousePos();
		const Rect<int> buttonRect = { absolutePosition(), absolutePosition() + _size };

		if (Contains(buttonRect, mousePos) && S2D->_inputManager->IsMouseButtonReleased(SDL_BUTTON_LEFT))
		{
			return true;
		}
		return false;
	}
};