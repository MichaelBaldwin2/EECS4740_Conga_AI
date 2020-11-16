#pragma once

#include "Agent.h"
#include <random>

class RandomPlayer : public Agent
{
private:
	std::mt19937 random;

public:
	RandomPlayer();
	Move GetMove(Board board, SDL_MouseButtonEvent& mb);
};
