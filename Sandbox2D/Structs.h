#pragma once

struct RGBA 
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

//! Creates an RGBA struct using alpha
inline RGBA MakeRGBA(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	return RGBA{ red, green, blue, alpha };
}

//! Creates an RGBA struct with alpha = 255
inline RGBA MakeRGBA(Uint8 red, Uint8 green, Uint8 blue)
{
	return RGBA{ red, green, blue, 255 };
}
