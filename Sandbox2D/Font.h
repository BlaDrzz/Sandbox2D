#pragma once

struct Font 
{
	//! Index in case there are multiple fonts in one TTF file.
	//! Defaults to -1.
	long index;
	//! Size in px
	int size;
	//! Resource _path
	std::string path;

	Font(const std::string path, const int size, const long index = -1) : index(index), size(size), path(path)
	{
		update();
	}

	~Font()
	{
		if (TTFfont != nullptr)
		{
			TTF_CloseFont(TTFfont);
			TTFfont = nullptr;
		}
	}

	TTF_Font* TTFfont = nullptr;

	//! (re-)initialises the TTF_Font.
	void update()
	{
		if (TTFfont != nullptr) TTF_CloseFont(TTFfont);

		if (index == -1) TTFfont = TTF_OpenFont(path.c_str(), size);
		else TTFfont = TTF_OpenFontIndex(path.c_str(), size, index);

		if (TTFfont == nullptr) std::cout << TTF_GetError() << std::endl;
	}
};