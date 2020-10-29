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

SpriteBatch::SpriteBatch() : renderer(), isDrawing(false), infos() {}

SpriteBatch::SpriteBatch(const Renderer renderer) : renderer(renderer), isDrawing(false), infos() {}

void SpriteBatch::Begin()
{
	if(isDrawing)
	{
		spdlog::warn("Already drawing using this SpriteBatch, call end() first!");
		return;
	}

	infos.clear();
	isDrawing = true;
}

void SpriteBatch::End()
{
	//Sort by depth and then texture
	std::sort(infos.begin(), infos.end(), [](const auto& first, const auto& second)
		{
			return first.depth < second.depth;
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
		const auto sdlTexture = info.sprite.GetTexture().GetSDLTexture();
		const auto srcRect = static_cast<SDL_Rect>(info.sprite.GetSrcRect());
		const SDL_Rect dstRect
		{
			static_cast<int>(info.position.x),
			static_cast<int>(info.position.y),
			static_cast<int>(static_cast<float>(info.sprite.GetSrcRect().GetWidth() * info.scale.x)),
			static_cast<int>(static_cast<float>(info.sprite.GetSrcRect().GetHeight() * info.scale.y))
		};
		const auto rotation = info.rotation;
		const auto center = static_cast<SDL_Point>(info.origin);
		const auto flip = static_cast<SDL_RendererFlip>(info.flip);

		SDL_SetTextureColorMod(sdlTexture, info.color.r, info.color.g, info.color.b);
		SDL_SetTextureAlphaMod(sdlTexture, info.color.a);
		SDL_RenderCopyEx(renderer.GetSDLRenderer(), sdlTexture, &srcRect, &dstRect, rotation, &center, flip);
	}

	isDrawing = false;
}

void SpriteBatch::Draw(const Sprite sprite, const Vector2 position, const Color color, const float rotation, const Vector2 origin, const Vector2 scale, const SpriteFlip flip, const float depth)
{
	SpriteInfo info{ sprite, position, color, rotation, origin, scale, flip, depth };
	infos.push_back(info);
}