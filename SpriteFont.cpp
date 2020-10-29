#include "RectInt.h"
#include "SpriteFont.h"

SpriteFont::SpriteFont() : characterSprites(), fontWidth(0), fontHeight(0) {}

SpriteFont::SpriteFont(const Texture& texture, const int spriteWidth, const int spriteHeight, const int numOfChars) : characterSprites(), fontWidth(spriteWidth), fontHeight(spriteHeight)
{
	for(auto y = 0, i = 0; y < texture.GetHeight(); y += spriteHeight)
	{
		for(auto x = 0; x < texture.GetWidth() && i < numOfChars; x += spriteWidth, i++)
		{
			auto rect = RectInt(x, y, spriteWidth, spriteHeight);
			auto sprite = Sprite(texture, rect);
			characterSprites.push_back(sprite);
		}
	}
}

Sprite SpriteFont::GetSprite(int character)
{
	return characterSprites[character];
}

int SpriteFont::GetFontWidth() const
{
	return fontWidth;
}

int SpriteFont::GetFontHeight() const
{
	return fontHeight;
}