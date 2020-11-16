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
	if(depth == 0 || state.board.CheckLoss("White") || state.board.CheckLoss("Black"))
	{
		exploredNodes++;
		state.evalValue = GetEvalValue5(state.board);
		return state;
	}

	if(isMax)
	{
		auto maxEval = BoardState{ state.board, state.move, -10000 };
		auto moves = GetMoves(name, state.board);
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
	else
	{
		auto minEval = BoardState{ state.board, state.move, 10000 };
		auto moves = GetMoves(name == "White" ? "Black" : "White", state.board);
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
	return static_cast<int>(GetMoves(name, board).size() - GetMoves(name == "White" ? "Black" : "White", board).size());
}

int AIPlayer::GetEvalValue2(Board board)
{
	// # player spaces to move to - # opponent spaces to move to
	auto playerMoves = GetMoves(name, board);
	auto opponentMoves = GetMoves(name == "White" ? "Black" : "White", board);
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
	return 128 - GetMoves(opponentName, board).size();
}

std::vector<Move> AIPlayer::GetMoves(std::string playerName, Board board)
{
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

	for(auto y = 0; y < 4; y++)
	{
		for(auto x = 0; x < 4; x++)
		{
			auto count = board.GetStoneCount(playerName, x, y);
			if(count <= 0)
			{
				continue;
			}
			else
			{
				for(auto i = 0; i < 8; i++)
				{
					if(board.CheckInput(playerName, x, y, directions[i]) == true)
					{
						possibleMoves.push_back({ x, y, directions[i] });
					}
				}
			}
		}
	}

	return possibleMoves;
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
