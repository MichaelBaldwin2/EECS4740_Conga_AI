#include "Minimax.h"

Minimax::Minimax(int horizon) : gameTree(), horizon(horizon)
{}

BoardState Minimax::GetOptimalMove(int depth, int nodeIndex, bool isMax) {
	if (depth == horizon) { return gameTree[nodeIndex]; }

	if (isMax) {
		BoardState first = GetOptimalMove(depth + 1, nodeIndex * 2, false);
		BoardState second = GetOptimalMove(depth + 1, nodeIndex * 2 + 1, false);

		return (first.evalValue >= second.evalValue) ? first : second;
	}
	else {
		BoardState first = GetOptimalMove(depth + 1, nodeIndex * 2, true);
		BoardState second = GetOptimalMove(depth + 1, nodeIndex * 2 + 1, true);

		return (first.evalValue <= second.evalValue) ? first : second;
	}
}

void Minimax::GenerateTree(bool isWhite, Board currentBoard)
{
	for(auto i = 0; i < horizon; i++)
	{

	}
}

std::vector<Move> Minimax::GetMoves(bool isWhite, Board board)
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

	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			int count = board.GetStoneCount(isWhite, x, y);
			if(count <= 0)
			{
				continue;
			}
			else
			{
				for(int i = 0; i < 8; i++)
				{
					if(board.CheckInput(isWhite, x, y, directions[i]) == true)
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

int Minimax::GetEvalValue(bool isWhite, Board board) {
	// Evaluation value is number of spaces adjacent to opponent
	int numSpaces = 0;

	for (auto y = 0; y < 4; y++) {
		for (auto x = 0; x < 4; x++) {
			if (board.GetStoneCount(!isWhite, x, y) <= 0) {
				continue;
			}
			else {
				if (board.GetStoneCount(isWhite, x + 1, y) > 0) {
					numSpaces++;
				}
				else if (board.GetStoneCount(isWhite, x - 1, y) > 0) {
					numSpaces++;
				}
				else if (board.GetStoneCount(isWhite, x, y + 1) > 0) {
					numSpaces++;
				}
				else if (board.GetStoneCount(isWhite, x, y - 1) > 0) {
					numSpaces++;
				}
				else if (board.GetStoneCount(isWhite, x + 1, y + 1) > 0) {
					numSpaces++;
				}
				else if (board.GetStoneCount(isWhite, x - 1, y + 1) > 0) {
					numSpaces++;
				}
				else if (board.GetStoneCount(isWhite, x + 1, y - 1) > 0) {
					numSpaces++;
				}
				else if (board.GetStoneCount(isWhite, x - 1, y - 1) > 0) {
					numSpaces++;
				}
			}
		}
	}

	return numSpaces;
}