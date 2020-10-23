#include "Game.h"
//#include <SDL.h>
//#include <spdlog/spdlog.h>

int main(int argc, char* args[])
{
	/*SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		spdlog::error("Failed to initilaize SDL2. SDL_Error:{0}", SDL_GetError());
		return -1;
	}*/

	auto game = Game(4, 4);
	game.Loop();
	return 0;
}