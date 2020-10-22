#pragma once

#include <vector>

class Board
{
private:
	unsigned int boardWidth;
	unsigned int boardHeight;
	std::vector<unsigned int> whiteStoneCounts;
	std::vector<unsigned int> blackStoneCounts;

public:
	Board(unsigned int boardWidth = 4, unsigned int boardHeight = 4);
	int GetStoneCount(bool white, unsigned int x, unsigned int y);
	int AddStones(bool white, unsigned int x, unsigned int y, unsigned int count);
	int RemoveStones(bool white, unsigned int x, unsigned int y);
	void PrintBoardToConsole();

private:
	bool CheckBounds(unsigned int x, unsigned int y);
};

