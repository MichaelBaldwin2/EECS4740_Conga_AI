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