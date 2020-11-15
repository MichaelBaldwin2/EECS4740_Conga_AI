#include "Renderer.h"
#include "Text.h"
#include "Texture.h"
#include "TTFFont.h"
#include "Sprite.h"
#include <SDL_ttf.h>
#include <spdlog/spdlog.h>
#include <string>

Text::Text() : font(), texture() {}

Text::Text(TTFFont font) : font(font), texture() {}

void Text::Free()
{
	texture.Free();
}

Sprite Text::RenderTextToSprite(Renderer renderer, std::string text)
{
	auto surface = TTF_RenderText_Solid(font.GetTTFFont(), text.c_str(), { 255, 255, 255, 255 });
	if(surface == nullptr)
	{
		spdlog::error("Failed to render ttf text to SDL_Surface! TTF_Error: {0}", TTF_GetError());
		SDL_FreeSurface(surface);
		surface = nullptr;
		return Sprite();
	}

	texture.Free();
	texture = Texture(renderer, surface);
	SDL_FreeSurface(surface);
	surface = nullptr;
	return Sprite(texture);
}
