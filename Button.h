#pragma once

#include "RectInt.h"
#include "Sprite.h"
#include "SpriteBatch.h"

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

