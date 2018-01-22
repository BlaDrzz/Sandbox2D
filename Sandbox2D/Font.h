#pragma once

struct Font 
{
	~Font()
	{
		if (_TTFfont != nullptr)
		{
			TTF_CloseFont(_TTFfont);
			_TTFfont = nullptr;
		}
	}

	TTF_Font* _TTFfont = nullptr;

	//! Index in case there are multiple fonts in one TTF file.
	//! Defaults to -1.
	long index;
	//! Size in px
	int size;
	//! Resource path
	std::string path;

	//! (re-)initialises the TTF_Font.
	void update()
	{
		if (_TTFfont != nullptr) TTF_CloseFont(_TTFfont);

		if (index == -1) _TTFfont = TTF_OpenFont(path.c_str(), size);
		else _TTFfont = TTF_OpenFontIndex(path.c_str(), size, index);

		if (_TTFfont == nullptr) std::cout << TTF_GetError() << std::endl;
	}
};

//! Returns a new font pointer based on path, _size and optionally index
inline Font* make_font(std::string path, int size, long index = -1)
{
	Font* f = new Font();
	f->path = path;
	f->size = size;
	f->index = index;
	f->update();

	return f;
}