#include "AIPlayer.h"
#include "BoardState.h"
#include <iostream>

Move AIPlayer::GetMove(Board& board, SDL_MouseButtonEvent& mb) {
	Move move = Move();
	move = Minimax({ board, {3, 3, -1}, 0 }, 3, -10000, 10000, true).move;
	totalDepth += 3;
	std::cout << "Search Depth: " << totalDepth << std::endl;
	std::cout << "Nodes Explored: " << exploredNodes << std::endl;
	std::cout << "Nodes Pruned: " << prunedNodes << std::endl;
	return move;
}

BoardState AIPlayer::Minimax(BoardState state, int depth, int alpha, int beta, bool player)
{
	if(depth == 0 || state.board.CheckLoss(player) || state.board.CheckLoss(!player))
	{
		exploredNodes++;
		state.evalValue = GetEvalValue2(player, state.board);
		return state;
	}

	if(player)
	{
		auto maxEval = BoardState{ state.board, state.move, -10000 };
		auto moves = GetMoves(player, state.board);
		for(auto i = 0; i < moves.size(); i++)
		{
			auto boardWithMove = state.board;
			boardWithMove.MoveStones(player, moves[i].x, moves[i].y, moves[i].direction);
			auto eval = Minimax({ boardWithMove, moves[i], 0 }, depth - 1, alpha, beta, !player);
			exploredNodes++;

			if(eval.evalValue >= maxEval.evalValue)
			{
				maxEval = { boardWithMove, moves[i], eval.evalValue };
			}
			alpha = std::max(alpha, eval.evalValue);
			if (beta <= alpha) {
				prunedNodes++;
				break;
			}
		}
		return maxEval;
	}
	else
	{
		auto minEval = BoardState{ state.board, state.move, 10000 };
		auto moves = GetMoves(player, state.board);
		for(auto i = 0; i < moves.size(); i++)
		{
			auto boardWithMove = state.board;
			boardWithMove.MoveStones(player, moves[i].x, moves[i].y, moves[i].direction);
			auto eval = Minimax({ boardWithMove, moves[i], 0 }, depth - 1, alpha, beta, !player);
			exploredNodes++;

			if (eval.evalValue <= minEval.evalValue) {
				minEval = { boardWithMove, moves[i], eval.evalValue };
			}
			beta = std::min(beta, eval.evalValue);
			if (beta <= alpha) {
				prunedNodes++;
				break;
			}
		}
		return minEval;
	}
}

int AIPlayer::GetEvalValue2(bool player, Board board) {
	// # opponent spaces to move to - # player spaces to move to
	auto opponentMoves = GetMoves(!player, board);
	auto playerMoves = GetMoves(player, board);
	int evalValue = 0;

	for (int i = 0; i < opponentMoves.size(); i++) {
		Board tempBoard = board;
		evalValue += tempBoard.MoveStones(!player, opponentMoves[i].x, opponentMoves[i].y, opponentMoves[i].direction);
	}

	for (int j = 0; j < playerMoves.size(); j++) {
		Board tempBoard = board;
		evalValue -= tempBoard.MoveStones(player, playerMoves[j].x, playerMoves[j].y, playerMoves[j].direction);
	}

	return evalValue;
}

int AIPlayer::GetEvalValue1(bool player, Board board) {
	// # opponent moves - # player moves
	return GetMoves(!player, board).size() - GetMoves(player, board).size();
}

std::vector<Move> AIPlayer::GetMoves(bool player, Board board) {
	std::vector<Move> possibleMoves;
	const int directions[] = {
		85,		// Up
		68,		// Down
		76,		// Left
		82,		// Right
		165,	// Northwest
		147,	// Northeast
		170,	// Southwest
		152		// Southeast
	};

	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			int count = board.GetStoneCount(player, x, y);
			if(count <= 0)
			{
				continue;
			}
			else
			{
				for(int i = 0; i < 8; i++)
				{
					if(board.CheckInput(player, x, y, directions[i]) == true)
					{
						Move move;
						move.x = x;
						move.y = y;
						move.direction = directions[i];
						possibleMoves.push_back(move);
					}
				}
			}
		}
	}

	return possibleMoves;
}