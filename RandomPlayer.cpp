#include "RandomPlayer.h"
#include <string>
#include <random>
#include <iostream>

Move RandomPlayer::GetMove(Board& board, SDL_MouseButtonEvent& mb) {
	bool validMove = false;
	const int directions[] = {
		85,		// Up
		68,		// Down
		76,		// Left
		82,		// Right
		165,	// Northwest
		147,	// Northeast
		170,	// Southwest
		152		// Southeast
	};

	Move move = Move();
	std::random_device rd;
	//std::mt19937 gen(rd()); // seed the generator
	std::mt19937 gen(123456); // seed the generator
	std::uniform_int_distribution<> coordDistr(0, 3);
	std::uniform_int_distribution<> dirDistr(0, 7);

	while (!validMove) {
		move.x = coordDistr(gen);
		move.y = coordDistr(gen);
		move.direction = directions[dirDistr(gen)];

		validMove = board.CheckInput(
			(this->name.compare("White") == 0),
			move.x,
			move.y,
			move.direction
		);
	}
    
	return move;
}
