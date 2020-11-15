#pragma once

#include "Color.h"
#include "Renderer.h"
#include "Sprite.h"
#include "SpriteFlip.h"
#include "SpriteFont.h"
#include "TTFFont.h"
#include "Vector2.h"
#include <vector>

struct SpriteInfo
{
	Sprite sprite;
	Vector2 position;
	Color color;
	float rotation;
	Vector2 origin;
	Vector2 scale;
	SpriteFlip flip;
	float depth;
};

class SpriteBatch
{
public:
	Renderer renderer;

private:
	bool isDrawing;
	std::vector<SpriteInfo> infos;

public:
	SpriteBatch();
	SpriteBatch(Renderer renderer);
	void Begin();
	void End();
	void Draw(Sprite sprite, Vector2 position, Color color = Color::White, float rotation = 0, Vector2 origin = Vector2::Zero, Vector2 scale = Vector2::One, SpriteFlip flip = SpriteFlip::None, float depth = 0.0f);
	void Draw(std::string text, SpriteFont spriteFont, Vector2 position, Color color = Color::White, float rotation = 0, Vector2 origin = Vector2::Zero, Vector2 scale = Vector2::One, SpriteFlip flip = SpriteFlip::None, float depth = 0.0f);
};