#include "AIPlayer.h"
#include "BoardState.h"
#include <iostream>

Move AIPlayer::GetMove(Board& board, SDL_MouseButtonEvent& mb) {
	Move move = Move();
	return Minimax({ board, {3, 3, -1}, 0 }, 3, true).move;
}

BoardState AIPlayer::Minimax(BoardState state, int depth, bool player)
{
	if(depth == 0 || state.board.CheckLoss(player))
	{
		state.evalValue = GetEvalValue(player, state.board);
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
			auto eval = Minimax({ boardWithMove, moves[i], 0 }, depth - 1, !player);

			if(eval.evalValue >= maxEval.evalValue)
			{
				maxEval = { boardWithMove, moves[i], eval.evalValue };
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
			auto eval = Minimax({ boardWithMove, moves[i], 0 }, depth - 1, !player);

			if (eval.evalValue <= minEval.evalValue) {
				minEval = { boardWithMove, moves[i], eval.evalValue };
			}
		}
		return minEval;
	}
}

// TODO FIX THIS
int AIPlayer::GetEvalValue(bool player, Board board) {
	// Evaluation value is number of spaces adjacent to opponent
	int count = 0;

	for (auto y = 0; y < 4; y++) {
		for (auto x = 0; x < 4; x++) {
			if (board.GetStoneCount(!player, x, y) <= 0) {
				continue;
			}
			else {
				if (board.GetStoneCount(player, x + 1, y) > 0) {
					count++;
				}
				else if (board.GetStoneCount(player, x - 1, y) > 0) {
					count++;
				}
				else if (board.GetStoneCount(player, x, y + 1) > 0) {
					count++;
				}
				else if (board.GetStoneCount(player, x, y - 1) > 0) {
					count++;
				}
				else if (board.GetStoneCount(player, x + 1, y + 1) > 0) {
					count++;
				}
				else if (board.GetStoneCount(player, x - 1, y + 1) > 0) {
					count++;
				}
				else if (board.GetStoneCount(player, x + 1, y - 1) > 0) {
					count++;
				}
				else if (board.GetStoneCount(player, x - 1, y - 1) > 0) {
					count++;
				}
			}
		}
	}

	return count;
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