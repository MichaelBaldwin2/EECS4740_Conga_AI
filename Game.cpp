#include "Board.h"
#include "Game.h"
#include <iostream>
#include <string>
//#include <SDL.h>

Game::Game() : board(), currentPlayer(0)
{
	board.AddStones(false, 0, 0, 10);
	board.AddStones(true, 3, 3, 10);

	board.PrintBoardToConsole();
}

void Game::Loop()
{
	bool isRunning = true;
	int direction = -1;
	int x, y;
	std::string nextMove, currentPlayerName;

	while(isRunning)
	{
		/* CONSOLE INPUT
		*	Input should be of the form "xyd1{d2}" where:
		*	- x is the x coordinate of the pieces to move
		*	- y is the y coordinate of the pieces to move
		*	- d1{d2} is the direction to move the pieces (U, D, L, R or NW, NE, SW, SE)
		*/
		currentPlayerName = (currentPlayer == 0) ? "Black" : "White";
		std::cout << "Enter move for " << currentPlayerName << ": ";
		std::cin >> nextMove;

		// Parse and check input
		if (nextMove[0] == 'q' || nextMove[0] == 'Q') {
			isRunning = false;
		}
		else if (nextMove.length() != 3 && nextMove.length() != 4) {
			std::cout << "ERROR: Please enter a valid command." << std::endl;
		}
		else {
			switch (nextMove.length()) {
			case 3:
				direction = nextMove[2];
			case 4:
				direction = nextMove[2] + nextMove[3];
			}
			x = nextMove[0] - 48;
			y = nextMove[1] - 48;

			if (Game::CheckInput(x, y, direction)) {
				// Move stones and print board
				Game::MoveStones(x, y, direction);
				board.PrintBoardToConsole();

				// Change currentPlayer
				switch (currentPlayer) {
				case 0:
					currentPlayer = 1;
					break;
				case 1:
					currentPlayer = 0;
					break;
				}
			}
		}
		// Win condition checking

		// Rendering
	}
}

bool Game::CheckInput(int x, int y, int direction) {
	const int validDirections[] = {
		85, 117,	// Up
		68, 100,	// Down
		76, 108,	// Left
		82, 114,	// Right
		165, 229,	// Northwest
		147, 211,	// Northeast
		170, 234,	// Southwest
		152, 216,	// Southeast
		-1
	};
	int errorCount = 0;
	bool white = !(currentPlayer == 0);

	if (x < 0 || x > 3) {
		std::cout << "ERROR: Please enter a valid x coordinate." << std::endl;
		return false;
	}
	if (y < 0 || y > 3) {
		std::cout << "ERROR: Please enter a valid y coordinate." << std::endl;
		return false;
	}
	if (std::find(std::begin(validDirections), std::end(validDirections), direction) == std::end(validDirections)) {
		std::cout << "ERROR: Please enter a valid direction." << std::endl;
		return false;
	}
	if (board.GetStoneCount(white, x, y) == 0) {
		std::cout << "ERROR: Must select current player's stones." << std::endl;
		return false;
	}
	// Up
	if (direction == 85 || direction == 117) {
		return (board.GetStoneCount(!white, x, y - 1) == 0);
	}
	// Down
	else if (direction == 68 || direction == 100) {
		return (board.GetStoneCount(!white, x, y + 1) == 0);
	}
	// Left
	else if (direction == 76 || direction == 108) {
		return (board.GetStoneCount(!white, x - 1, y) == 0);
	}
	// Right
	else if (direction == 82 || direction == 114) {
		return (board.GetStoneCount(!white, x + 1, y) == 0);
	}
	// Northwest
	else if (direction == 165 || direction == 229) {
		return (board.GetStoneCount(!white, x - 1, y - 1) == 0);
	}
	// Northeast
	else if (direction == 147 || direction == 211) {
		return (board.GetStoneCount(!white, x + 1, y - 1) == 0);
	}
	// Southwest
	else if (direction == 170 || direction == 234) {
		return (board.GetStoneCount(!white, x - 1, y + 1) == 0);
	}
	// Southeast
	else if (direction == 152 || direction == 216) {
		return (board.GetStoneCount(!white, x + 1, y + 1) == 0);
	}
	else {
		return false;
	}
}

void Game::MoveStones(int x, int y, int direction) {
	bool white = !(currentPlayer == 0);
	int numStones = board.RemoveStones(white, x, y);
	int freeSpaces = 0;
	int addX[3], addY[3];

	// Determine number of free spaces
	for (int i = 1; i < 4; i++) {
		// Up
		if (direction == 85 || direction == 117) {
			if (board.GetStoneCount(!white, x, y - i) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
			addX[i - 1] = x;
			addY[i - 1] = y - i;
		}
		// Down
		else if (direction == 68 || direction == 100) {
			if (board.GetStoneCount(!white, x, y + i) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
			addX[i - 1] = x;
			addY[i - 1] = y + i;
		}
		// Left
		else if (direction == 76 || direction == 108) {
			if (board.GetStoneCount(!white, x - i, y) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
			addX[i - 1] = x - i;
			addY[i - 1] = y;
		}
		// Right
		else if (direction == 82 || direction == 114) {
			if (board.GetStoneCount(!white, x + i, y) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
			addX[i - 1] = x + i;
			addY[i - 1] = y;
		}
		// Northwest
		if (direction == 165 || direction == 229) {
			if (board.GetStoneCount(!white, x - i, y - i) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
			addX[i - 1] = x - i;
			addY[i - 1] = y - i;
		}
		// Northeast
		else if (direction == 147 || direction == 211) {
			if (board.GetStoneCount(!white, x + i, y - i) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
			addX[i - 1] = x + i;
			addY[i - 1] = y - i;
		}
		// Southwest
		else if (direction == 170 || direction == 234) {
			if (board.GetStoneCount(!white, x - i, y + i) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
			addX[i - 1] = x - i;
			addY[i - 1] = y + i;
		}
		// Southeast
		else if (direction == 152 || direction == 216) {
			if (board.GetStoneCount(!white, x + i, y + i) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
			addX[i - 1] = x + i;
			addY[i - 1] = y + i;
		}
	}

	// Place stones in correct spaces
	switch (freeSpaces) {
	case 1:
		board.AddStones(white, addX[0], addY[0], numStones);
		break;
	case 2:
		board.AddStones(white, addX[0], addY[0], 1);
		numStones--;
		if (numStones > 0) { board.AddStones(white, addX[1], addY[1], numStones); }
		break;
	case 3:
		board.AddStones(white, addX[0], addY[0], 1);
		numStones--;
		if (numStones >= 2) { board.AddStones(white, addX[1], addY[1], 2); }
		else { board.AddStones(white, addX[1], addY[1], numStones); }
		numStones -= 2;
		if (numStones > 0) { board.AddStones(white, addX[2], addY[2], numStones); }
		break;
	}
}
