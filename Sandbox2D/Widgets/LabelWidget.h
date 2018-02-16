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
	void draw(Graphics* g) override
	{
		if (_hidden) return;
		g->drawString(_text, absolutePosition());
	}
};