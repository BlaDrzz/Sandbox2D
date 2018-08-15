#pragma once

/**
* \brief Represents a panelwidget (Subclass of Widget)
*/
struct PanelWidget : Widget
{
	/**
	* \brief Constructor
	* @param position: a Pixel
	*/
	PanelWidget(Pixel position)
	{
		_position = position;
	};

	/**
	* \brief Constructor
	* @param position: a Pixel
	* @param widgetArr: a reference of a std::vector<Widget*> object
	*/
	PanelWidget(Pixel position, const std::vector<Widget*> &widgetArr) : _widgets(widgetArr)
	{
		_position = position;
	};
	
	/**
	* \brief Destructor
	*/
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

	/**
	* \brief Add the widget
	* @param widget: a pointer to a widget
	* @return A pointer to a widget
	*/
	Widget* add(Widget* widget)
	{
		widget->_parent = this;

		_widgets.push_back(widget);

		return widget;
	}

	//! Collection of _widgets
	std::vector<Widget*> _widgets;

	/**
	* \brief Tick function
	* @param deltaTime: a double
	*/
	void tick(double deltaTime) override
	{
		for (auto w : _widgets)
		{
			w->tick(deltaTime);
		}
	}

	/**
	* \brief Draw function
	* @param g: pointer to a Graphics object
	*/
	void draw(Graphics* g) override
	{
		if (!_hidden) return;
		
		for (auto w : _widgets)
		{
			w->draw(g);
		}
	}
};