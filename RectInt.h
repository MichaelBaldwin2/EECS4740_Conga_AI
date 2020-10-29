
#pragma once

#include "Vector2Int.h"
#include <SDL.h>

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

	explicit operator SDL_Rect() const;
};