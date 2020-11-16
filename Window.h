/* Window.h
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include <SDL.h>
#include <string>

/// <summary>
/// Wrapper for SDL_Window
/// </summary>
class Window
{
private:
	SDL_Window* sdlWindow;

public:
	Window();
	Window(int width, int height, std::string title = "SDL2 Window", int xPos = SDL_WINDOWPOS_UNDEFINED, int yPos = SDL_WINDOWPOS_UNDEFINED, Uint32 flags = SDL_WINDOW_SHOWN);
	void Free();
	SDL_Window* GetSDLWindow() const;
};