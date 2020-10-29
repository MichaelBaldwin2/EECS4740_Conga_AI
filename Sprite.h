#pragma once

#include "RectInt.h"
#include "Texture.h"
#include <string>

class Sprite
{
private:
	Texture texture;
	RectInt srcRect;

public:
	Sprite();
	Sprite(Texture texture);
	Sprite(Texture texture, const RectInt srcRect);
	Texture GetTexture() const;
	RectInt GetSrcRect() const;
};