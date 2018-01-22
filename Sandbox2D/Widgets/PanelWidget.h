#pragma once

struct PanelWidget : Widget
{
	// Constructor
	PanelWidget(Pixel position)
	{
		_position = position;
	};
	PanelWidget(Pixel position, const std::vector<Widget*> &widgetArr) : _widgets(widgetArr)
	{
		_position = position;
	};
	// Destructor
	~PanelWidget()
	{
		for (auto w : _widgets)
		{
			if (w != nullptr)
			{
				delete w;
			}
		}
	}

	Widget* add(Widget* widget)
	{
		widget->_parent = this;

		_widgets.push_back(widget);

		return widget;
	}

	// Collection of _widgets
	std::vector<Widget*> _widgets;

	void tick(double deltaTime) override
	{
		for (auto w : _widgets)
		{
			w->tick(deltaTime);
		}
	}

	void draw() override
	{
		if (!_hidden) return;
		
		for (auto w : _widgets)
		{
			w->draw();
		}
	}
};