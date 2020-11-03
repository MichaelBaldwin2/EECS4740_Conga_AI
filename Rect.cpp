#include "Rect.h"

Rect::Rect() : min(), max() {}

Rect::Rect(const Vector2 min, const Vector2 max) : min(min), max(max) {}

Rect::Rect(const float x, const float y, const float w, const float h) : min(Vector2(x, y)), max(Vector2(x + w, y + h)) {}

float Rect::GetX() const
{
	return min.x;
}

float Rect::GetY() const
{
	return min.y;
}

float Rect::GetWidth() const
{
	return max.x - min.x;
}

float Rect::GetHeight() const
{
	return max.y - min.y;
}