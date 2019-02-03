#pragma once

/**
* \brief Represents an RGBA color
*/
struct RGBA 
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

/**
* \brief Creates an RGBA struct using alpha
* @param red: a Uint8 object
* @param green: a Uint8 object
* @param blue: a Uint8 object
* @param alpha: a Uint8 object
* @return An RGBA color object
*/
inline RGBA MakeRGBA(const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha)
{
	return RGBA{ red, green, blue, alpha };
}

/**
* \brief Creates an RGBA struct with alpha = 255
* @param red: a Uint8 object
* @param green: a Uint8 object
* @param blue: a Uint8 object
* @return An RGBA color object
*/
inline RGBA MakeRGBA(const Uint8 red, const Uint8 green, const Uint8 blue)
{
	return RGBA{ red, green, blue, 255 };
}

struct Colors
{
	static RGBA white();
	static RGBA black();
	static RGBA gray();
	static RGBA red();
	static RGBA green();
	static RGBA blue();
	static RGBA yellow();
};
inline RGBA Colors::white() { return MakeRGBA(255, 255, 255); }
inline RGBA Colors::gray() { return MakeRGBA(128, 128, 125); }
inline RGBA Colors::black() { return MakeRGBA(0, 0, 0); }
inline RGBA Colors::red() { return MakeRGBA(255, 0, 0); }
inline RGBA Colors::green() { return MakeRGBA(0, 255, 0); }
inline RGBA Colors::blue() { return MakeRGBA(0, 0, 255); }
inline RGBA Colors::yellow() { return MakeRGBA(255, 255, 0); }