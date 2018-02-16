#pragma once

struct Bitmap
{
	SDL_Surface* _surface = nullptr;
	std::string _path;

	Bitmap(const std::string path) : _path(path)
	{
		update();
	}

	~Bitmap()
	{
		if (_surface != nullptr)
		{
			SDL_FreeSurface(_surface);
			_surface = nullptr;
		}
	}

	void update() 
	{
		if (_surface != nullptr) SDL_FreeSurface(_surface);

		// Create a new _surface
		_surface = IMG_Load(_path.c_str());
		if (_surface == nullptr) printf("Cannot load PNG at location: '%s', SDL Error: %s", _path.c_str(), SDL_GetError());
	}

	Pixel getSize() const
	{
		return _surface != nullptr ? 
			Pixel{
				_surface->w,
				_surface->h
			} : Pixel{ 0, 0 };
	}
};