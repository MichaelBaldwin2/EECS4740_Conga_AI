/* Sprite.cpp
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "RectInt.h"
#include "Sprite.h"
#include "Texture.h"
#include <string>

Sprite::Sprite() : texture(), srcRect() {}

Sprite::Sprite(const Texture texture) : texture(texture), srcRect(RectInt(0, 0, texture.GetWidth(), texture.GetHeight())) {}

Sprite::Sprite(const Texture texture, const RectInt srcRect) : texture(texture), srcRect(srcRect) {}

Texture Sprite::GetTexture() const
{
	return texture;
}

RectInt Sprite::GetSrcRect() const
{
	return srcRect;
}