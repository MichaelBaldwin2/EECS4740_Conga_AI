/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

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