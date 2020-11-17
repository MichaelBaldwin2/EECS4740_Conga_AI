/* AIPlayer.h
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

/// <summary>
/// AI Player.
/// Uses the Minimax algorithm with alpha-beta pruning
/// </summary>
class AIPlayer : public Agent
{
private:
	int totalDepth = 0;
	int exploredNodes = 0;
	int prunedNodes = 0;

public:
	Move GetMove(Board board, SDL_MouseButtonEvent& mb);

	/// <summary>
	/// Recursive minimax function with alpha-beta pruning
	/// </summary>
	/// <returns></returns>
	BoardState Minimax(BoardState state, int depth, int alpha, int beta, bool player);
	/// <summary>
	/// Evaluation function
	/// # of max moves - # of min moves
	/// </summary>
	int GetEvalValue1(Board board);
	/// <summary>
	/// Evaluation function
	/// # player spaces to move to - # opponent spaces to move to
	/// </summary>
	int GetEvalValue2(Board board);
	/// <summary>
	/// Evaluation function
	/// # of black spaces - # of white spaces
	/// </summary>
	int GetEvalValue3(Board board);
	/// <summary>
	/// Evaluation function
	/// # of moves that the opponent has
	/// </summary>
	int GetEvalValue4(Board board);
	int GetTotalDepth();
	int GetExploredNodes();
	int GetPrunedNodes();
};