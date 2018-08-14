#pragma once

#define S2D (Sandbox2D::GetSingleton())

/**
* \brief Represents a bitmapwidget (Subclass of Widget)
*/
struct BitmapWidget : Widget
{
	/**
	* \brief Bitmap* _bitmap
	*/
	Bitmap* _bitmap;

	/**
	* \brief Constructor
	* @param bitmap: pointer to a bitmap
	* @param position: a Pixel
	*/
	BitmapWidget(Bitmap* bitmap, Pixel position)
	{
		_bitmap = bitmap;
		_position = position;
	}

	/**
	* \brief Destructor
	*/
	~BitmapWidget() {}

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
		g->drawBitmap(_bitmap, absolutePosition());
	}
};