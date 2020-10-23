#pragma once

#include "Board.h"

class Game
{
private:
	Board board;
	bool isRunning;

public:
	Game(int boardWidth = 4, int boardHeight = 4);
	void Loop();
};

