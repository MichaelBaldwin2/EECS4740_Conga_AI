/* Main.cpp
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 * 
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <spdlog/spdlog.h>

bool Init();
void Shutdown();

/// <summary>
/// Program entry point
/// </summary>
int main(int argc, char* args[])
{
	if(!Init())
	{
		return -1;
	}

	spdlog::info("Initializing Game...");
	auto game = new Game(); // Using a pointer so that we cna control when the destructor is called
	if(!game->Init())
	{
		spdlog::error("Failed to initialize game!");
		return false;
	}

	spdlog::info("Starting game...");
	game->Loop();
	delete game;

	Shutdown();
	return 0;
}

/// <summary>
/// Initializes all the subsystems
/// </summary>
bool Init()
{
	spdlog::info("Initializing...");

	spdlog::info("Initializing SDL2...");
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		spdlog::error("SDL2 couldn't initialize! SDL_Error: {}", SDL_GetError());
		return false;
	}

	spdlog::info("Initializing SDL_Image...");
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		spdlog::error("SDL_image could not be initialized! SDL_image Error: {}", IMG_GetError());
		return false;
	}

	spdlog::info("Initializing SDL_TTF...");
	if(TTF_Init() == -1)
	{
		spdlog::error("SDL_ttf could not be initialized! SDL_ttf Error: {}", TTF_GetError());
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	return true;
}

/// <summary>
/// Shuts down and releases subsystems
/// </summary>
void Shutdown()
{
	spdlog::info("Shutting down...");

	spdlog::info("Quitting SDL_TTF...");
	TTF_Quit();
	spdlog::info("Quitting SDL_Image...");
	IMG_Quit();
	spdlog::info("Quitting SDL2...");
	SDL_Quit();
}
