#pragma once

/**
* \brief Represents a Font
*/
struct Font 
{
	/**
	* \brief Index in case there are multiple fonts in one TTF file (Defaults to -1)
	*/
	long index;
	
	/**
	* \brief Size of the font in px
	*/
	int size;
	
	/**
	* \brief Resource path
	*/
	std::string path;

	/**
	* \brief Constructor
	* @param path: a string as path
	* @param size: an integer
	* @param index: a long (default = -1)
	*/
	Font(const std::string path, const int size, const long index = -1) : index(index), size(size), path(path)
	{
		update();
	}

	/**
	* \brief Destructor
	*/
	~Font()
	{
		if (TTFfont != nullptr)
		{
			TTF_CloseFont(TTFfont);
			TTFfont = nullptr;
		}
	}

	/**
	* \brief TTF Font
	*/
	TTF_Font* TTFfont = nullptr;

	/**
	* \brief (re-)initialises the TTF_Font
	*/
	void update()
	{
		if (TTFfont != nullptr) TTF_CloseFont(TTFfont);

		if (index == -1) TTFfont = TTF_OpenFont(path.c_str(), size);
		else TTFfont = TTF_OpenFontIndex(path.c_str(), size, index);

		if (TTFfont == nullptr) std::cout << TTF_GetError() << std::endl;
	}
};