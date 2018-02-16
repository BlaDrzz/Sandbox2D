#pragma once

struct RGBA 
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

//! Creates an RGBA struct using alpha
inline RGBA MakeRGBA(const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha)
{
	return RGBA{ red, green, blue, alpha };
}

//! Creates an RGBA struct with alpha = 255
inline RGBA MakeRGBA(const Uint8 red, const Uint8 green, const Uint8 blue)
{
	return RGBA{ red, green, blue, 255 };
}