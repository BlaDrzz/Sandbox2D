#pragma once

#define S2D (Sandbox2D::GetSingleton())

/**
* \brief Represents a labelwidget (Subclass of Widget)
*/
struct LabelWidget : Widget
{
	std::string _text;

	/**
	* \brief Constructor
	* @param text: a string
	* @param position: a Pixel
	*/
	LabelWidget(std::string text, Pixel position) : _text(text)
	{
		_position = position;
	}
	
	/**
	* \brief Destructor
	*/
	~LabelWidget() {}

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
		g->drawString(_text, absolutePosition());
	}
};