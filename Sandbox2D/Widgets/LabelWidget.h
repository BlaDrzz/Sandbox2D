#pragma once

#define S2D (Sandbox2D::GetSingleton())

struct LabelWidget : Widget
{
	std::string _text;

	// Constructor
	LabelWidget(std::string text, Pixel position) : _text(text)
	{
		_position = position;
	}
	// Destructor
	~LabelWidget() {}

	void tick(double deltaTime) override {}
	void draw() override
	{
		if (_hidden) return;
		S2D->_graphics->drawString(_text, absolutePosition());
	}
};