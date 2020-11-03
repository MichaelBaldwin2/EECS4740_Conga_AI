#pragma once

#include "Sprite.h"
#include "Texture.h"
#include <vector>

class SpriteFont
{
private:
	std::vector<Sprite> characterSprites;
	int fontWidth;
	int fontHeight;

public:
	SpriteFont();
	SpriteFont(const Texture& texture, int spriteWidth, int spriteHeight, int numOfChars);
	Sprite GetSprite(int character);
	int GetFontWidth() const;
	int GetFontHeight() const;
};