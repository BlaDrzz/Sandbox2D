#pragma once

struct Widget
{
	virtual ~Widget() {};

	Pixel _position;
	Widget* _parent = nullptr;
	bool _hidden = false;

	Pixel absolutePosition() const
	{
		return _position + (_parent == nullptr ? Pixel{ 0,0 } : _parent->absolutePosition());
	}

	virtual void tick(double deltaTime) = 0;
	virtual void draw(Graphics* g) = 0;
};

// Include other widgets, resharper might think these are obsolete includes but THEY ARE NOT!
#include "PanelWidget.h"
#include "LabelWidget.h"
#include "BitmapWidget.h"
#include "ButtonWidget.h"
