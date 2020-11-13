#pragma once

#include "Board.h"
#include "Move.h"

struct BoardState
{
	Board board;
	Move move;
	int evalValue;
};
