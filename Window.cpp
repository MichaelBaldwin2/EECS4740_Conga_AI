/* Window.cpp
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "Window.h"
#include <SDL.h>
#include <spdlog/spdlog.h>
#include <string>

Window::Window() : sdlWindow(nullptr) {}

Window::Window(const int width, const int height, const std::string title, const int xPos, const int yPos, const Uint32 flags) : Window()
{
	spdlog::info("Creating the window");
	sdlWindow = SDL_CreateWindow(title.c_str(), xPos, yPos, width, height, flags);
	if(sdlWindow == nullptr)
	{
		spdlog::error("Failed to create the SDL window. Error: {0}", SDL_GetError());
	}
}

void Window::Free()
{
	SDL_DestroyWindow(sdlWindow);
	sdlWindow = nullptr;
}

SDL_Window* Window::GetSDLWindow() const
{
	return sdlWindow;
}