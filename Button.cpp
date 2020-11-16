/* Button.cpp
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "Button.h"
#include "RectInt.h"
#include "Sprite.h"
#include "SpriteBatch.h"

Button::Button() : rectInt(), sprite(), pressedColor(), isPressed() {}

Button::Button(RectInt rectInt, Sprite sprite, Color pressedColor) : rectInt(rectInt), sprite(sprite), pressedColor(pressedColor), isPressed() {}

void Button::OnDown()
{
	isPressed = true;
}

void Button::OnUp()
{
	isPressed = false;
}

void Button::OnRender(SpriteBatch & spriteBatch)
{
	spriteBatch.Draw(sprite, Vector2(static_cast<float>(rectInt.GetX()), static_cast<float>(rectInt.GetY())), isPressed ? pressedColor : Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.1f);
}

bool Button::ContainsPoint(Vector2Int point)
{
	return rectInt.ContainsPoint(point);
}
