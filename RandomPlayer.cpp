#include "RandomPlayer.h"
#include <string>
#include <random>
#include <iostream>

Move RandomPlayer::GetMove() {
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
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> coordDistr(0, 3);
	std::uniform_int_distribution<> dirDistr(0, 7);

	move.x = coordDistr(gen);
	move.y = coordDistr(gen);
	move.direction = directions[dirDistr(gen)];
	
    return move;
}
