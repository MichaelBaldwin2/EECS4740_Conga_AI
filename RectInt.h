/* RectInt.h
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */


#pragma once

#include "Vector2Int.h"

/// <summary>
/// A integer rectangle class
/// </summary>
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