/* Button.h
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include "RectInt.h"
#include "Sprite.h"
#include "SpriteBatch.h"

/// <summary>
/// Helper class representing a GUI button
/// </summary>
class Button
{
private:
	RectInt rectInt;
	Sprite sprite;
	Color pressedColor;
	bool isPressed;

public:
	Button();
	Button(RectInt rectInt, Sprite sprite, Color pressedColor);
	void OnDown();
	void OnUp();
	void OnRender(SpriteBatch& spriteBatch);
	bool ContainsPoint(Vector2Int point);
};

