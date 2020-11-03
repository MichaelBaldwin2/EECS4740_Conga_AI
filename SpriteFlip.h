#pragma once

#include <SDL.h>

enum class SpriteFlip : int
{
	None = SDL_FLIP_NONE,
	Horizontal = SDL_FLIP_HORIZONTAL,
	Vertical = SDL_FLIP_VERTICAL
};