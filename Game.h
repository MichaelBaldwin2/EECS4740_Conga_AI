#pragma once

#include "Board.h"

class Game
{
private:
	Board board;
	int currentPlayer;
	int CheckInput(int x, int y, int direction);
	int CheckInputDirection(int x, int y, int direction);
	void MoveStones(int x, int y, int direction);

public:
	Game();
	void Loop();
};

