#pragma once

#include "Board.h"
#include "Move.h"
#include <vector>

struct BoardState
{
	Board board;
	unsigned int evalValue;
};

class Minimax
{
private:
	std::vector<BoardState> gameTree;
	int horizon;

public:
	Minimax(int horizon = 2);
	void GenerateTree(bool isWhite, Board currentBoard);
	int GetNumberOfMoves(bool isWhite, Board board);
	std::vector<Move> GetMoves(bool isWhite, Board board);
};

