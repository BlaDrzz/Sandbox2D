#pragma once

/**
* \brief Represents a Bitmap
*/

struct Bitmap
{
	/**
	* \brief SDL_Surface of the bitmap
	*/
	SDL_Surface* _surface = nullptr;

	/**
	* \brief Path of the image to convert to a bitmap
	*/
	std::string _path;

	/**
	* \brief Constructor
	* @param path: a string as path
	*/
	Bitmap(const std::string path) : _path(path)
	{
		update();
	}

	/**
	* \brief Destructor
	*/
	~Bitmap()
	{
		if (_surface != nullptr)
		{
			SDL_FreeSurface(_surface);
			_surface = nullptr;
		}
	}

	/**
	* \brief Update the bitmap
	*/
	void update() 
	{
		if (_surface != nullptr) SDL_FreeSurface(_surface);

		// Create a new _surface
		_surface = IMG_Load(_path.c_str());
		if (_surface == nullptr) printf("Cannot load PNG at location: '%s', SDL Error: %s", _path.c_str(), SDL_GetError());
	}

	/**
	* \brief Gets the size of the bitmap
	* @return Pixel
	*/
	Pixel getSize() const
	{
		return _surface != nullptr ? 
			Pixel{
				_surface->w,
				_surface->h
			} : Pixel{ 0, 0 };
	}
};