#pragma once

#include "Agent.h"
#include "BoardState.h"

class AIPlayer : public Agent
{
public:
	Move GetMove(Board& board, SDL_MouseButtonEvent& mb);
	BoardState Minimax(BoardState state, int depth, bool player);
	int GetEvalValue(bool player, Board board);
	std::vector<Move> GetMoves(bool isWhite, Board board);
};