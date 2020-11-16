/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "AIPlayer.h"
#include "BoardState.h"
#include <iostream>

Move AIPlayer::GetMove(Board board, SDL_MouseButtonEvent& mb)
{
	Move move = Move();
	move = Minimax({ board, {0, 0, -1}, 0 }, 3, -10000, 10000, true).move;
	totalDepth += 3;
	return move;
}

BoardState AIPlayer::Minimax(BoardState state, int depth, int alpha, int beta, bool isMax)
{
	// If we have either reached a leaf node or one of the players has lost on this board state, then calculate the static evaluation
	if(depth == 0 || state.board.CheckLoss("White") || state.board.CheckLoss("Black"))
	{
		exploredNodes++;
		state.evalValue = GetEvalValue5(state.board);
		return state;
	}

	// Is it maxes turn?
	if(isMax)
	{
		/*
		* Create a new board state
		* Get a list of possible moves max can make on this state
		* simulate the moves for each state, calling minimax recursivly for each move
		* If the proposed move results in a more favorable outcome, then return it
		* Prune branches where it will be impossible to achieve better results
		*/
		auto maxEval = BoardState{ state.board, state.move, -10000 };
		auto moves = state.board.GetMoves(name);
		for(auto i = 0; i < moves.size(); i++)
		{
			auto boardWithMove = state.board;
			boardWithMove.MoveStones(name, moves[i].x, moves[i].y, moves[i].direction);
			auto eval = Minimax({ boardWithMove, moves[i], 0 }, depth - 1, alpha, beta, !isMax);
			exploredNodes++;

			if(eval.evalValue > maxEval.evalValue)
			{
				maxEval = { boardWithMove, moves[i], eval.evalValue };
			}
			alpha = std::max(alpha, eval.evalValue);
			if(beta <= alpha)
			{
				prunedNodes++;
				break;
			}
		}
		return maxEval;
	}
	else // If it is mins turn
	{
		/*
		* Create a new board state
		* Get a list of possible moves min can make on this state
		* simulate the moves for each state, calling minimax recursivly for each move
		* If the proposed move results in a more favorable outcome, then return it
		* Prune branches where it will be impossible to achieve better results
		*/
		auto minEval = BoardState{ state.board, state.move, 10000 };
		auto moves = state.board.GetMoves(name == "White" ? "Black" : "White");
		for(auto i = 0; i < moves.size(); i++)
		{
			auto boardWithMove = state.board;
			boardWithMove.MoveStones(name == "White" ? "Black" : "White", moves[i].x, moves[i].y, moves[i].direction);
			auto eval = Minimax({ boardWithMove, moves[i], 0 }, depth - 1, alpha, beta, !isMax);
			exploredNodes++;

			if(eval.evalValue < minEval.evalValue)
			{
				minEval = { boardWithMove, moves[i], eval.evalValue };
			}
			beta = std::min(beta, eval.evalValue);
			if(beta <= alpha)
			{
				prunedNodes++;
				break;
			}
		}
		return minEval;
	}
}

int AIPlayer::GetEvalValue1(Board board)
{
	// # max moves - # min moves
	return static_cast<int>(board.GetMoves(name).size() - board.GetMoves(name == "White" ? "Black" : "White").size());
}

int AIPlayer::GetEvalValue2(Board board)
{
	// # player spaces to move to - # opponent spaces to move to
	auto playerMoves = board.GetMoves(name);
	auto opponentMoves = board.GetMoves(name == "White" ? "Black" : "White");
	auto evalValue = 0;

	for(int i = 0; i < playerMoves.size(); i++)
	{
		auto tempBoard = board;
		evalValue += tempBoard.MoveStones(name, playerMoves[i].x, playerMoves[i].y, playerMoves[i].direction);
	}

	for(int i = 0; i < opponentMoves.size(); i++)
	{
		auto tempBoard = board;
		evalValue -= tempBoard.MoveStones(name == "White" ? "Black" : "White", opponentMoves[i].x, opponentMoves[i].y, opponentMoves[i].direction);
	}

	return evalValue;
}//*/

int AIPlayer::GetEvalValue3(Board board)
{
	auto blackCellCount = 0;
	auto whiteCellCount = 0;

	for(auto y = 0; y < 4; y++)
	{
		for(auto x = 0; x < 4; x++)
		{
			blackCellCount += board.GetStoneCount("Black", x, y) > 0 ? 1 : 0;
			whiteCellCount += board.GetStoneCount("White", x, y) > 0 ? 1 : 0;
		}
	}

	return blackCellCount - whiteCellCount;
}

int AIPlayer::GetEvalValue4(Board board)
{
	/*
	* AI Player wants to maximize the number of opponent cells that are adjacent to itself (AI Player) or the wall.
	*/

	return 0;
}

int AIPlayer::GetEvalValue5(Board board)
{
	auto opponentName = name == "White" ? "Black" : "White";
	return 128 - static_cast<int>(board.GetMoves(opponentName).size());
}

int AIPlayer::GetTotalDepth()
{
	return totalDepth;
}

int AIPlayer::GetExploredNodes()
{
	return exploredNodes;
}

int AIPlayer::GetPrunedNodes()
{
	return prunedNodes;
}
