#pragma once

#include "Board.h"
#include "Move.h"
#include <string>

class Agent
{
public:
	std::string name;

public:
	virtual Move GetMove(Board& board) = 0;
};
