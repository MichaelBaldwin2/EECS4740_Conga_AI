#pragma once

#include "Board.h"
#include "Move.h"
#include <vector>

struct BoardState
{
	Board board;
	Move move;
	int evalValue;
};

class Minimax
{
private:
	int horizon;

public:
	std::vector<BoardState> gameTree;
	Minimax(int horizon = 2);
	BoardState GetOptimalMove(int depth, int nodeIndex, bool isMax);
	void GenerateTree(bool isWhite, Board currentBoard);
	std::vector<Move> GetMoves(bool isWhite, Board board);
	int GetEvalValue(bool isWhite, Board board);
};

