/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

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