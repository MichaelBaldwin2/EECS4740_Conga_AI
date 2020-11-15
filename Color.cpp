#include "Color.h"
#include <SDL.h>
#include <algorithm>

const Color Color::Clear = Color(0, 0, 0, 0);
const Color Color::Black = Color(0, 0, 0, 255);
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
const Color Color::Magenta = Color(255, 0, 255, 255);

Color::Color(const int r, const int g, const int b, const int a)
	: r(std::clamp(r, 0, 256)),
	g(std::clamp(g, 0, 256)),
	b(std::clamp(b, 0, 256)),
	a(std::clamp(a, 0, 256))
{}

Color::Color(const float r, const float g, const float b, const float a)
	: r(std::clamp(static_cast<int>(r * 256.0f), 0, 256)),
	g(std::clamp(static_cast<int>(g * 256.0f), 0, 256)),
	b(std::clamp(static_cast<int>(b * 256.0f), 0, 256)),
	a(std::clamp(static_cast<int>(a * 256.0f), 0, 256))
{}

Color::operator SDL_Color() const
{
	return { r, g, b, a };
}

bool operator==(const Color& first, const Color& second)
{
	return first.r == second.r && first.g == second.g && first.b == second.b && first.a == second.a;
}

bool operator!=(const Color& first, const Color& second)
{
	return !(first == second);
}