#include "Board.h"

int main()
{
	auto board = Board(4, 4);
	board.AddStones(false, 0, 0, 10);
	board.AddStones(true, 3, 3, 10);

	board.PrintBoardToConsole();

	return 0;
}