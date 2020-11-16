/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include <string>
#include <vector>

class Board
{
private:
	int whiteStoneCounts[4][4];
	int blackStoneCounts[4][4];

public:
	Board();

	int GetStoneCount(const char* player, unsigned int x, unsigned int y);
	int AddStones(const char* player, unsigned int x, unsigned int y, unsigned int count);
	int RemoveStones(const char* player, unsigned int x, unsigned int y);
	bool CheckInput(const char* player, int x, int y, int direction);
	int MoveStones(const char* player, unsigned int x, unsigned int y, unsigned int direction);
	bool CheckLoss(const char* player);

	int GetStoneCount(std::string player, unsigned int x, unsigned int y);
	int AddStones(std::string player, unsigned int x, unsigned int y, unsigned int count);
	int RemoveStones(std::string player, unsigned int x, unsigned int y);
	bool CheckInput(std::string player, int x, int y, int direction);
	int MoveStones(std::string player, unsigned int x, unsigned int y, unsigned int direction);
	bool CheckLoss(std::string player);

	void PrintBoardToConsole();
	bool operator ==(Board board);

private:
	int GetStoneCount(bool white, unsigned int x, unsigned int y);
	int AddStones(bool white, unsigned int x, unsigned int y, unsigned int count);
	int RemoveStones(bool white, unsigned int x, unsigned int y);
	bool CheckInput(bool white, int x, int y, int direction);
	int MoveStones(bool white, unsigned int x, unsigned int y, unsigned int direction);
	bool CheckLoss(bool white);

private:
	bool CheckBounds(unsigned int x, unsigned int y);
};
