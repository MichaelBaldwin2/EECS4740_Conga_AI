#pragma once

#include <SDL.h>
#include <string>

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