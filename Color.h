#pragma once

#include <SDL.h>

class Color
{
public:
	const static Color Clear;
	const static Color Black;
	const static Color White;
	const static Color Red;
	const static Color Green;
	const static Color Blue;
	const static Color Magenta;

public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

public:
	Color(int r = 0, int g = 0, int b = 0, int a = 255);
	Color(float r, float g, float b, float a = 1.0f);

	explicit operator SDL_Color() const;
	friend bool operator==(const Color& first, const Color& second);
	friend bool operator!=(const Color& first, const Color& second);
};