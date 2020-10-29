#pragma once

#include "Vector2.h"

class Rect
{
private:
	Vector2 min;
	Vector2 max;

public:
	Rect();
	Rect(Vector2 min, Vector2 max);
	Rect(float x, float y, float w, float h);
	float GetX() const;
	float GetY() const;
	float GetWidth() const;
	float GetHeight() const;
};