
#pragma once

#include "Vector2Int.h"

class RectInt
{
private:
	Vector2Int min;
	Vector2Int max;

public:
	RectInt();
	RectInt(Vector2Int min, Vector2Int max);
	RectInt(int x, int y, int w, int h);
	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;
	bool ContainsPoint(Vector2Int point);
};