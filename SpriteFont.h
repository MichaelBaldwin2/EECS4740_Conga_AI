/* SpriteFont.h
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include "Sprite.h"
#include "Texture.h"
#include <vector>

/// <summary>
/// A class used to render text to the screen. Doesn't look good.
/// </summary>
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