#include "Minimax.h"

Minimax::Minimax(int horizon) : gameTree(), horizon(horizon)
{}


void Minimax::GenerateTree(bool isWhite, Board currentBoard)
{
	Board newBoard = Board();
	BoardState state;

	// Initial state
	state.board = currentBoard;
	state.evalValue = 0; // Determine evalValue
	gameTree.push_back(state);

	std::vector<Move> possibleMoves = GetMoves(isWhite, currentBoard);
	int numberPossibleMoves = GetNumberOfMoves(isWhite, currentBoard);

	for (int i = 0; i < numberPossibleMoves; i++) {
		newBoard = currentBoard; // Copy current board
		newBoard.MoveStones(isWhite, possibleMoves[i].x, possibleMoves[i].y, possibleMoves[i].direction);

		state.board = newBoard;
		state.evalValue = 0;// Calculate new evalValue;
		gameTree.push_back(state);
	}
}

int Minimax::GetNumberOfMoves(bool isWhite, Board board)
{
	int numOfMoves = 0;

	for(auto y = 0; y < 4; y++)
	{
		for(auto x = 0; x < 4; x++)
		{

		}
	}

	return numOfMoves;
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
				Move move;
				for(int i = 0; i < 8; i++)
				{
					if(board.CheckInput(isWhite, x, y, directions[i]) == true)
					{
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