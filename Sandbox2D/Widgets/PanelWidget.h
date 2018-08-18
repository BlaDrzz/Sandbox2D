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
	PanelWidget(const Pixel position)
	{
		this->position = position;
	};

	/**
	* \brief Constructor
	* @param position: a Pixel
	* @param widgetArr: a reference of a std::vector<Widget*> object
	*/
	PanelWidget(const Pixel position, std::vector<Widget*> widgetArr) : _widgets(std::move(widgetArr))
	{
		this->position = position;
	};
	
	/**
	* \brief Destructor
	*/
	~PanelWidget()
	{
		for (auto w : _widgets)
		{
			delete w;
		}
	}

	/**
	* \brief Add the widget
	* @param widget: a pointer to a widget
	* @return A pointer to a widget
	*/
	Widget* add(Widget* widget)
	{
		widget->parent = this;

		_widgets.push_back(widget);

		return widget;
	}

	//! Collection of _widgets
	std::vector<Widget*> _widgets;

	/**
	* \brief Tick function
	* @param deltaTime: a double
	*/
	void tick(const double deltaTime) override
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
		if (hidden) return;
		
		for (auto w : _widgets)
		{
			w->draw(g);
		}
	}
};