#pragma once

#include "Agent.h"
#include "BoardState.h"
#include <string>

class AIPlayer : public Agent
{
private:
	int totalDepth = 0;
	int exploredNodes = 0;
	int prunedNodes = 0;

public:
	Move GetMove(Board board, SDL_MouseButtonEvent& mb);
	void OnRender(SpriteBatch& spriteBatch, SpriteFont font);
	BoardState Minimax(BoardState state, int depth, int alpha, int beta, bool player);
	int GetEvalValue1(Board board);
	int GetEvalValue2(Board board);
	std::vector<Move> GetMoves(std::string player, Board board);
};