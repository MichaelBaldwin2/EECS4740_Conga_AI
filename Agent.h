#pragma once

#include "Board.h"
#include <string>

struct Move
{
	int x, y;
	int direction;
};

class Agent
{
public:
	std::string name;

public:
	virtual Move GetMove(Board& board) = 0;
};
