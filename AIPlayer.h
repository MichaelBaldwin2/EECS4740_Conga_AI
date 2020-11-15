#pragma once

#include "Agent.h"
#include "BoardState.h"

class AIPlayer : public Agent
{
private:
	int totalDepth = 0;
	int exploredNodes = 0;
	int prunedNodes = 0;

public:
	Move GetMove(Board& board, SDL_MouseButtonEvent& mb);
	BoardState Minimax(BoardState state, int depth, int alpha, int beta, bool player);
	int GetEvalValue2(bool player, Board board);
	int GetEvalValue1(bool player, Board board);
	std::vector<Move> GetMoves(bool isWhite, Board board);
};