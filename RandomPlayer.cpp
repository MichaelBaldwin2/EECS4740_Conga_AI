#include "RandomPlayer.h"
#include <string>
#include <random>
#include <iostream>

RandomPlayer::RandomPlayer()
{
	std::random_device rd;
	random = std::mt19937(rd()); // seed the generator
	//random = std::mt19937(0); // seed the generator
}

Move RandomPlayer::GetMove(Board board, SDL_MouseButtonEvent& mb)
{
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

	auto coordDistr = std::uniform_int_distribution<>(0, 3);
	auto dirDistr = std::uniform_int_distribution <>(0, 7);
	Move move = Move();

	while(!validMove)
	{
		move.x = coordDistr(random);
		move.y = coordDistr(random);
		move.direction = directions[dirDistr(random)];

		validMove = board.CheckInput(
			name,
			move.x,
			move.y,
			move.direction
		);
	}

	return move;
}
