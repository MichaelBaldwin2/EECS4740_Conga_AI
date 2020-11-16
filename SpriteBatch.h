/* SpriteBatch.h
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include "Color.h"
#include "Renderer.h"
#include "Sprite.h"
#include "SpriteFlip.h"
#include "SpriteFont.h"
#include "TTFFont.h"
#include "Vector2.h"
#include <vector>

/// <summary>
/// Helper structure to hold information about how to draw a sprite
/// </summary>
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

/// <summary>
/// Fast sprite rendering, uses depth sorting and attempts to minimize texture switching on the gpu
/// </summary>
class SpriteBatch
{
public:
	Renderer renderer;

private:
	bool isDrawing;
	std::vector<SpriteInfo> infos;
	std::vector<Texture> tempTextures;

public:
	SpriteBatch();
	SpriteBatch(Renderer renderer);
	void Free();
	void Begin();
	void End();
	void Draw(Sprite sprite, Vector2 position, Color color = Color::White, float rotation = 0, Vector2 origin = Vector2::Zero, Vector2 scale = Vector2::One, SpriteFlip flip = SpriteFlip::None, float depth = 0.0f);
	void Draw(std::string text, SpriteFont spriteFont, Vector2 position, Color color = Color::White, float rotation = 0, Vector2 origin = Vector2::Zero, Vector2 scale = Vector2::One, SpriteFlip flip = SpriteFlip::None, float depth = 0.0f);
	void Draw(std::string text, TTFFont font, Vector2 position, Color color = Color::White, float rotation = 0, Vector2 origin = Vector2::Zero, Vector2 scale = Vector2::One, SpriteFlip flip = SpriteFlip::None, float depth = 0.0f);
};