#pragma once

#include "Color.h"
#include "Window.h"
#include <SDL.h>

class Renderer
{
private:
	SDL_Renderer* sdlRenderer;

public:
	Renderer();
	Renderer(Window window, int index = -1, Uint32 flags = SDL_RENDERER_ACCELERATED);
	void Free();
	SDL_Renderer* GetSDLRenderer() const;
	void ClearScreen(Color color) const;
	void PresentScreen() const;
};