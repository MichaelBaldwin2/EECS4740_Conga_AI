/* RectInt.cpp
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "RectInt.h"

RectInt::RectInt() : min(), max() {}

RectInt::RectInt(const Vector2Int min, const Vector2Int max) : min(min), max(max) {}

RectInt::RectInt(const int x, const int y, const int w, const int h) : min(Vector2Int(x, y)), max(Vector2Int(x + w, y + h)) {}

int RectInt::GetX() const
{
	return min.x;
}

int RectInt::GetY() const
{
	return min.y;
}

int RectInt::GetWidth() const
{
	return max.x - min.x;
}

int RectInt::GetHeight() const
{
	return max.y - min.y;
}

bool RectInt::ContainsPoint(Vector2Int point)
{
	if(point.x < min.x)
	{
		return false;
	}
	if(point.x > max.x)
	{
		return false;
	}
	if(point.y < min.y)
	{
		return false;
	}
	if(point.y > max.y)
	{
		return false;
	}

	return true;
}