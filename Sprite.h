/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include "RectInt.h"
#include "Texture.h"
#include <string>

/// <summary>
/// Represents a drawable part (or full) of a Texture
/// </summary>
class Sprite
{
private:
	Texture texture;
	RectInt srcRect;

public:
	Sprite();
	Sprite(Texture texture);
	Sprite(Texture texture, const RectInt srcRect);
	Texture GetTexture() const;
	RectInt GetSrcRect() const;
};