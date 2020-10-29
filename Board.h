#pragma once

#include "Sprite.h"
#include <vector>

class Board
{
private:
	unsigned int whiteStoneCounts[4][4];
	unsigned int blackStoneCounts[4][4];
	Sprite sprite;

public:
	Board(Sprite* sprite = nullptr);
	int GetStoneCount(bool white, unsigned int x, unsigned int y);
	int AddStones(bool white, unsigned int x, unsigned int y, unsigned int count);
	int RemoveStones(bool white, unsigned int x, unsigned int y);
	void PrintBoardToConsole();
	Sprite GetSprite();

private:
	bool CheckBounds(unsigned int x, unsigned int y);
};

