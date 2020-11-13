#pragma once

#include "Agent.h"
#include "Minimax.h"

class AIPlayer : public Agent
{
private:
	Minimax minimax;

public:
	Move GetMove(Board& board);
};