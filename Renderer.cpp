/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "Color.h"
#include "Renderer.h"
#include "Window.h"
#include <SDL.h>
#include <spdlog/spdlog.h>

Renderer::Renderer() : sdlRenderer(nullptr) {}

Renderer::Renderer(const Window window, const int index, const Uint32 flags) : Renderer()
{
	spdlog::info("Creating the renderer");
	sdlRenderer = SDL_CreateRenderer(window.GetSDLWindow(), index, flags);
	if(sdlRenderer == nullptr)
	{
		spdlog::error("Failed to create the SDL Renderer. Error: {0}", SDL_GetError());
	}
}

void Renderer::Free()
{
	SDL_DestroyRenderer(sdlRenderer);
	sdlRenderer = nullptr;
}

SDL_Renderer* Renderer::GetSDLRenderer() const
{
	return sdlRenderer;
}

void Renderer::ClearScreen(Color color) const
{
	SDL_SetRenderDrawColor(GetSDLRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderClear(GetSDLRenderer());
}

void Renderer::PresentScreen() const
{
	SDL_RenderPresent(GetSDLRenderer());
}