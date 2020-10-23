#include "Board.h"
#include "Game.h"
//#include <SDL.h>

Game::Game(int boardWidth, int boardHeight) : board(boardWidth, boardHeight)
{
	board.AddStones(false, 0, 0, 10);
	board.AddStones(true, 3, 3, 10);

	board.PrintBoardToConsole();
}

void Game::Loop()
{
	while(isRunning)
	{
		// Input Event polling (mouse keyboard)

		// Update functionality, board update, logic running. This would be qwhere Minimax algo would run at.

		// Rendering
	}
}
