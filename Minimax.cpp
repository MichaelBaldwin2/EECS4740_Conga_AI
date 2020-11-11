#include "Minimax.h"

Minimax::Minimax(int horizon) : gameTree(), horizon(horizon)
{}


void Minimax::GenerateTree(Board currentBoard)
{
	BoardState state;
	state.board = currentBoard;
	state.evalValue = 3;
	gameTree.push_back(state);

	for (int i = 1; i <= horizon; i++) {
		GetNumberOfMoves(false, currentBoard);
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

std::vector<> Game::GetMoves
{
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
			int count = board.GetStoneCount((player == whitePlayer), x, y);
			if(count <= 0)
			{
				continue;
			}
			else
			{
				for(int i = 0; i < 8; i++)
				{
					if(board.CheckInput((player == whitePlayer), x, y, directions[i]) == true)
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}