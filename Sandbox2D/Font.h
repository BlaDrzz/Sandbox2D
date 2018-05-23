#pragma once

struct Font 
{
	//! Index in case there are multiple fonts in one TTF file.
	//! Defaults to -1.
	long _index;
	//! Size in px
	int _size;
	//! Resource _path
	std::string _path;

	Font(const std::string path, const int size, const long index = -1) : _path(path), _size(size), _index(index)
	{
		update();
	}

	~Font()
	{
		if (_TTFfont != nullptr)
		{
			TTF_CloseFont(_TTFfont);
			_TTFfont = nullptr;
		}
	}

	TTF_Font* _TTFfont = nullptr;

	//! (re-)initialises the TTF_Font.
	void update()
	{
		if (_TTFfont != nullptr) TTF_CloseFont(_TTFfont);

		if (_index == -1) _TTFfont = TTF_OpenFont(_path.c_str(), _size);
		else _TTFfont = TTF_OpenFontIndex(_path.c_str(), _size, _index);

		if (_TTFfont == nullptr) std::cout << TTF_GetError() << std::endl;
	}
};