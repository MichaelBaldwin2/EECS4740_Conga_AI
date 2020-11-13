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
	Board newBoard = Board();
	BoardState state;

	// Initial state
	state.board = currentBoard;
	state.evalValue = GetEvalValue(isWhite, newBoard);
	gameTree.push_back(state);

	for (int i = 1; i <= horizon; i++) {
		bool player;
		if (i % 2 == 0) {
			player = !isWhite;
		}
		else {
			player = isWhite;
		}

		std::vector<Move> possibleMoves = GetMoves(player, currentBoard);
		int numberPossibleMoves = GetNumberOfMoves(player, currentBoard);

		for (int j = 0; j < numberPossibleMoves; j++) {
			Move move = possibleMoves[j];
			newBoard = currentBoard; // Copy current board
			newBoard.MoveStones(player, possibleMoves[j].x, possibleMoves[j].y, possibleMoves[j].direction);

			state.board = newBoard;
			state.move = move;
			state.evalValue = GetEvalValue(isWhite, newBoard);
			gameTree.push_back(state);
		}
	}
}

int Minimax::GetNumberOfMoves(bool isWhite, Board board)
{
	int numOfMoves = 0;
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

	for(auto y = 0; y < 4; y++)	{
		for(auto x = 0; x < 4; x++) {
			if (board.GetStoneCount(isWhite, x, y) <= 0) {
				continue;
			}
			else {
				for (auto i = 0; i < 8; i++) {
					if (board.CheckInput(isWhite, x, y, directions[i])) { 
						numOfMoves++;
					}
				}
			}
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