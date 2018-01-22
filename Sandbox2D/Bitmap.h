#pragma once

struct Bitmap
{
	~Bitmap()
	{
		if (_surface != nullptr)
		{
			SDL_FreeSurface(_surface);
			_surface = nullptr;
		}
	}

	SDL_Surface* _surface = nullptr;
	std::string path;

	void Update() 
	{
		if (_surface != nullptr) SDL_FreeSurface(_surface);

		// Create a new _surface
		_surface = IMG_Load(path.c_str());
		if (_surface == nullptr) printf("Cannot load PNG at location: '%s', SDL Error: %s", path.c_str(), SDL_GetError());
	}
};

inline Bitmap* make_bitmap(std::string path)
{
	Bitmap* b = new Bitmap();
	b->path = path;
	b->Update();

	return b;
}