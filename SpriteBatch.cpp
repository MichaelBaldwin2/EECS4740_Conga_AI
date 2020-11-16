/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "Color.h"
#include "Renderer.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "SpriteFlip.h"
#include "Vector2.h"
#include <SDL.h>
#include <spdlog/spdlog.h>
#include <algorithm>
#include <vector>

SpriteBatch::SpriteBatch() : renderer(), isDrawing(false), infos(), tempTextures() {}

SpriteBatch::SpriteBatch(const Renderer renderer) : renderer(renderer), isDrawing(false), infos() {}

void SpriteBatch::Free()
{
	for(auto it = tempTextures.begin(); it != tempTextures.end(); it++)
	{
		it->Free();
	}

	tempTextures.clear();
	infos.clear();
}

void SpriteBatch::Begin()
{
	if(isDrawing)
	{
		spdlog::warn("Already drawing using this SpriteBatch, call end() first!");
		return;
	}

	// Free and clear all temp textures and previous sprite infos
	for(auto it = tempTextures.begin(); it != tempTextures.end(); it++)
	{
		it->Free();
	}

	tempTextures.clear();
	infos.clear();
	isDrawing = true;
}

void SpriteBatch::End()
{
	//Sort by depth and then texture
	std::sort(infos.begin(), infos.end(), [](const auto& first, const auto& second)
		{
			return first.depth > second.depth;
			//if(first.depth < second.depth)
			//{
			//	return true;
			//}
			//else if(first.depth > second.depth)
			//{
			//	return false;
			//}

			//// There is no 'true' way to sort textures, so I just use their address locations lol
			//return &(first.sprite.GetTexture()) < &(second.sprite.GetTexture());
		});

	// Call draw on the sorted sprites
	for(const SpriteInfo info : infos)
	{
		const auto srcRect = SDL_Rect{ info.sprite.GetSrcRect().GetX(), info.sprite.GetSrcRect().GetY(), info.sprite.GetSrcRect().GetWidth(), info.sprite.GetSrcRect().GetHeight() };
		const SDL_Rect dstRect
		{
			static_cast<int>(info.position.x),
			static_cast<int>(info.position.y),
			static_cast<int>(static_cast<float>(info.sprite.GetSrcRect().GetWidth() * info.scale.x)),
			static_cast<int>(static_cast<float>(info.sprite.GetSrcRect().GetHeight() * info.scale.y))
		};
		const auto origin = SDL_Point{ static_cast<int>(info.origin.x), static_cast<int>(info.origin.y) };

		SDL_SetTextureColorMod(info.sprite.GetTexture().GetSDLTexture(), info.color.r, info.color.g, info.color.b);
		SDL_SetTextureAlphaMod(info.sprite.GetTexture().GetSDLTexture(), info.color.a);
		SDL_RenderCopyEx(renderer.GetSDLRenderer(), info.sprite.GetTexture().GetSDLTexture(), &srcRect, &dstRect, info.rotation, &origin, static_cast<SDL_RendererFlip>(info.flip));
	}

	isDrawing = false;
}

void SpriteBatch::Draw(const Sprite sprite, const Vector2 position, const Color color, const float rotation, const Vector2 origin, const Vector2 scale, const SpriteFlip flip, const float depth)
{
	SpriteInfo info{ sprite, position, color, rotation, origin, scale, flip, depth };
	infos.push_back(info);
}

void SpriteBatch::Draw(std::string text, SpriteFont spriteFont, Vector2 position, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteFlip flip, float depth)
{
	for(auto c = 0, x = 0, y = 0; c < text.length(); c++, x += spriteFont.GetFontWidth() / 2)
	{
		auto sprite = spriteFont.GetSprite(text[c]);
		Draw(sprite, position + (Vector2(static_cast<float>(x), static_cast<float>(y)) * scale), color, rotation, origin, scale, flip, depth);
	}
}

void SpriteBatch::Draw(std::string text, TTFFont font, Vector2 position, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteFlip flip, float depth)
{
	auto surface = TTF_RenderText_Blended(font.GetTTFFont(), text.c_str(), { color.r, color.g, color.b, color.a });
	if(surface == nullptr)
	{
		spdlog::error("Failed to render ttf text to SDL_Surface! TTF_Error: {0}", TTF_GetError());
		SDL_FreeSurface(surface);
		surface = nullptr;
		return;
	}

	auto texture = Texture(renderer, surface);
	tempTextures.push_back(texture);
	SDL_FreeSurface(surface);
	surface = nullptr;
	Draw(Sprite(texture), position, Color::White, rotation, origin, scale, flip, depth);
}
