#pragma once

#include "Agent.h"

class RandomPlayer : public Agent
{

public:
	Move GetMove(Board board, SDL_MouseButtonEvent& mb);
};
