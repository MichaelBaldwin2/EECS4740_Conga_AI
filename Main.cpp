#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>

bool Init();
void Shutdown();

int main(int argc, char* args[])
{
	if(!Init())
	{
		return -1;
	}

	spdlog::info("Initializing Game...");
	auto game = Game();
	if(!game.Init())
	{
		spdlog::error("Failed to initialize game!");
		return false;
	}

	spdlog::info("Starting game...");
	game.Loop();

	Shutdown();
	return 0;
}

bool Init()
{
	spdlog::info("Initializing...");

	spdlog::info("Initializing SDL2...");
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		spdlog::error("SDL2 couldn't initialize! SDL_Error: {}", SDL_GetError());
		return false;
	}

	spdlog::info("Initializing SDL_image...");
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		spdlog::error("SDL_image could not be initialized! SDL_image Error: {}", IMG_GetError());
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	return true;
}

void Shutdown()
{
	spdlog::info("Shutting down...");

	spdlog::info("Quitting SDL_Image...");
	IMG_Quit();
	spdlog::info("Quitting SDL2...");
	SDL_Quit();
}