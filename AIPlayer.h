/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

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
	BoardState Minimax(BoardState state, int depth, int alpha, int beta, bool player);
	int GetEvalValue1(Board board);
	int GetEvalValue2(Board board);
	int GetEvalValue3(Board board);
	int GetEvalValue4(Board board);
	int GetEvalValue5(Board board);
	std::vector<Move> GetMoves(std::string player, Board board);
	int GetTotalDepth();
	int GetExploredNodes();
	int GetPrunedNodes();
};