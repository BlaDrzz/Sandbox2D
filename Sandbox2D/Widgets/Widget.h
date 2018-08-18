#pragma once

/**
* \brief Represents a Widget
*/
struct Widget
{
	/**
	* \brief Constructor
	*/
	virtual ~Widget() {};

	Pixel position = { 0, 0 };
	Widget* parent = nullptr;
	bool hidden = false;

	/**
	* \brief Get absolute position of the widget
	* @return A Pixel
	*/
	Pixel absolutePosition() const
	{
		return position + (parent == nullptr ? Pixel{ 0,0 } : parent->absolutePosition());
	}

	/**
	* \brief Tick function
	* @param deltaTime: a double
	*/
	virtual void tick(double deltaTime) = 0;

	/**
	* \brief Draw function
	* @param g: pointer to a Graphics object
	*/
	virtual void draw(Graphics* g) = 0;
};

// Include other widgets, resharper might think these are obsolete includes but THEY ARE NOT!
#include "PanelWidget.h"
#include "LabelWidget.h"
#include "BitmapWidget.h"
#include "ButtonWidget.h"
