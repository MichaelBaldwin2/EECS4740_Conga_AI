#include "Button.h"

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
	spriteBatch.Draw(sprite, Vector2(rectInt.GetX(), rectInt.GetY()), isPressed ? pressedColor : Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.1f);
}

bool Button::ContainsPoint(Vector2Int point)
{
	return rectInt.ContainsPoint(point);
}
