#include "HumanPlayer.h"
#include <string>
#include <random>
#include <iostream>

/* CONSOLE INPUT
	*	Input should be of the form "xyd1{d2}" where:
	*	- x is the x coordinate of the pieces to move
	*	- y is the y coordinate of the pieces to move
	*	- d1{d2} is the direction to move the pieces (U, D, L, R or NW, NE, SW, SE)
*/
Move HumanPlayer::GetMove(Board& board) {
	bool validMove = false;
	Move move = Move();
	std::string input;

	while (!validMove) {
		std::cout << "Enter move for " << this->name << ": ";
		std::cin >> input;

		if (input.length() != 3 && input.length() != 4)
		{
			std::cout << "ERROR: Please enter a valid command." << std::endl;
		}
		else {
			switch (input.length())
			{
			case 3:
				move.direction = input[2];
				break;
			case 4:
				move.direction = input[2] + input[3];
				break;
			}
			move.x = input[0] - 48;
			move.y = input[1] - 48;

			validMove = board.CheckInput(
				(this->name.compare("White") == 0),
				move.x,
				move.y,
				move.direction
			);
		}
	}

	return move;
}
