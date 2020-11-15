#pragma once

#include <vector>

class Board
{
private:
	unsigned int whiteStoneCounts[4][4];
	unsigned int blackStoneCounts[4][4];

public:
	Board();
	int GetStoneCount(bool white, unsigned int x, unsigned int y);
	int AddStones(bool white, unsigned int x, unsigned int y, unsigned int count);
	int RemoveStones(bool white, unsigned int x, unsigned int y);
	void PrintBoardToConsole();
	bool CheckInput(bool white, int x, int y, int direction);
	int MoveStones(bool white, unsigned int x, unsigned int y, unsigned int direction);
	bool CheckLoss(bool white);
	bool operator ==(Board board);

private:
	bool CheckBounds(unsigned int x, unsigned int y);
};
