#pragma once

#include "Renderer.h"
#include "Texture.h"
#include "TTFFont.h"
#include "Sprite.h"
#include <SDL_ttf.h>
#include <string>

class Text
{
private:
	TTFFont font;
	Texture texture;

public:
	Text();
	Text(TTFFont font);
	void Free();
	Sprite RenderTextToSprite(Renderer renderer, std::string text);
};

