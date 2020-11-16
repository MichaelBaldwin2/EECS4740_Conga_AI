/* Board.cpp
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "Board.h"
#include "Move.h"
#include <iostream>
#include <sstream>
#include <vector>

Board::Board() : whiteStoneCounts(), blackStoneCounts()
{
	for(auto y = 0; y < 4; y++)
	{
		for(auto x = 0; x < 4; x++)
		{
			whiteStoneCounts[x][y] = 0;
			blackStoneCounts[x][y] = 0;
		}
	}
}

int Board::GetStoneCount(const char* player, unsigned int x, unsigned int y)
{
	return GetStoneCount(std::string(player), x, y);
}

int Board::AddStones(const char* player, unsigned int x, unsigned int y, unsigned int count)
{
	return AddStones(std::string(player), x, y, count);
}

int Board::RemoveStones(const char* player, unsigned int x, unsigned int y)
{
	return RemoveStones(std::string(player), x, y);
}

bool Board::CheckInput(const char* player, int x, int y, int direction)
{
	return CheckInput(std::string(player), x, y, direction);
}

int Board::MoveStones(const char* player, unsigned int x, unsigned int y, unsigned int direction)
{
	return MoveStones(std::string(player), x, y, direction);
}

bool Board::CheckLoss(const char* player)
{
	return CheckLoss(std::string(player));
}

std::vector<Move> Board::GetMoves(const char* player)
{
	return GetMoves(std::string(player));
}

int Board::GetStoneCount(std::string player, unsigned int x, unsigned int y)
{
	return GetStoneCount(player.compare("White") == 0, x, y);
}

int Board::AddStones(std::string player, unsigned int x, unsigned int y, unsigned int count)
{
	return AddStones(player.compare("White") == 0, x, y, count);
}

int Board::RemoveStones(std::string player, unsigned int x, unsigned int y)
{
	return RemoveStones(player.compare("White") == 0, x, y);
}

bool Board::CheckInput(std::string player, int x, int y, int direction)
{
	return CheckInput(player.compare("White") == 0, x, y, direction);
}

int Board::MoveStones(std::string player, unsigned int x, unsigned int y, unsigned int direction)
{
	return MoveStones(player.compare("White") == 0, x, y, direction);
}

bool Board::CheckLoss(std::string player)
{
	return CheckLoss(player.compare("White") == 0);
}

std::vector<Move> Board::GetMoves(std::string player)
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
			auto count = GetStoneCount(player, x, y);
			if(count <= 0)
			{
				continue;
			}
			else
			{
				for(auto i = 0; i < 8; i++)
				{
					if(CheckInput(player, x, y, directions[i]) == true)
					{
						possibleMoves.push_back({ x, y, directions[i] });
					}
				}
			}
		}
	}

	return possibleMoves;
}

int Board::GetStoneCount(bool white, unsigned int x, unsigned int y)
{
	if(CheckBounds(x, y))
	{
		return -1;
	}

	return white ? whiteStoneCounts[y][x] : blackStoneCounts[y][x];
}

int Board::AddStones(bool white, unsigned int x, unsigned int y, unsigned int count)
{
	if(CheckBounds(x, y))
	{
		return -1;
	}

	white ? whiteStoneCounts[y][x] += count : blackStoneCounts[y][x] += count;
	return GetStoneCount(white, x, y);
}

int Board::RemoveStones(bool white, unsigned int x, unsigned int y)
{
	if(CheckBounds(x, y))
	{
		return -1;
	}

	auto stoneCount = GetStoneCount(white, x, y);
	white ? whiteStoneCounts[y][x] = 0 : blackStoneCounts[y][x] = 0;
	return stoneCount;
}

void Board::PrintBoardToConsole()
{
	for(auto y = 0; y < 4; y++)
	{
		std::cout << "|";
		for(auto x = 0; x < 4; x++)
		{
			auto whiteCount = GetStoneCount(true, x, y);
			auto blackCount = GetStoneCount(false, x, y);

			std::cout << "| ";
			if(whiteCount == 0)
			{
				std::cout << "--";
			}
			else if(whiteCount < 10)
			{
				std::cout << "0" << whiteCount;
			}
			else
			{
				std::cout << whiteCount;
			}
			std::cout << "=";
			if(blackCount == 0)
			{
				std::cout << "--";
			}
			else if(blackCount < 10)
			{
				std::cout << "0" << blackCount;
			}
			else
			{
				std::cout << blackCount;
			}
			std::cout << " |";
		}
		std::cout << "|" << std::endl;
	}
}

bool Board::CheckBounds(unsigned int x, unsigned int y)
{
	return x >= 4 || y >= 4;
}

bool Board::CheckInput(bool white, int x, int y, int direction)
{
	const int validDirections[] = {
		85, 117,	// Up
		68, 100,	// Down
		76, 108,	// Left
		82, 114,	// Right
		165, 229,	// Northwest
		147, 211,	// Northeast
		170, 234,	// Southwest
		152, 216,	// Southeast
		-1
	};

	if(x < 0 || x > 3)
	{
		std::cout << "ERROR: Please enter a valid x coordinate." << std::endl;
		return false;
	}
	if(y < 0 || y > 3)
	{
		std::cout << "ERROR: Please enter a valid y coordinate." << std::endl;
		return false;
	}
	if(std::find(std::begin(validDirections), std::end(validDirections), direction) == std::end(validDirections))
	{
		if(direction != -1)
		{
			std::cout << "ERROR: Please enter a valid direction." << std::endl;
		}
		return false;
	}
	if(GetStoneCount(white, x, y) == 0)
	{
		return false;
	}
	// Up
	if(direction == 85 || direction == 117)
	{
		return (GetStoneCount(!white, x, y - 1) == 0);
	}
	// Down
	else if(direction == 68 || direction == 100)
	{
		return (GetStoneCount(!white, x, y + 1) == 0);
	}
	// Left
	else if(direction == 76 || direction == 108)
	{
		return (GetStoneCount(!white, x - 1, y) == 0);
	}
	// Right
	else if(direction == 82 || direction == 114)
	{
		return (GetStoneCount(!white, x + 1, y) == 0);
	}
	// Northwest
	else if(direction == 165 || direction == 229)
	{
		return (GetStoneCount(!white, x - 1, y - 1) == 0);
	}
	// Northeast
	else if(direction == 147 || direction == 211)
	{
		return (GetStoneCount(!white, x + 1, y - 1) == 0);
	}
	// Southwest
	else if(direction == 170 || direction == 234)
	{
		return (GetStoneCount(!white, x - 1, y + 1) == 0);
	}
	// Southeast
	else if(direction == 152 || direction == 216)
	{
		return (GetStoneCount(!white, x + 1, y + 1) == 0);
	}
	else
	{
		return false;
	}
}

int Board::MoveStones(bool white, unsigned int x, unsigned int y, unsigned int direction)
{
	int numStones = RemoveStones(white, x, y);
	int freeSpaces = 0;
	int addX[3], addY[3];

	// Determine number of free spaces
	for(int i = 1; i < 4; i++)
	{
		// Up
		if(direction == 85 || direction == 117)
		{
			if(GetStoneCount(!white, x, y - i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x;
			addY[i - 1] = y - i;
		}
		// Down
		else if(direction == 68 || direction == 100)
		{
			if(GetStoneCount(!white, x, y + i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x;
			addY[i - 1] = y + i;
		}
		// Left
		else if(direction == 76 || direction == 108)
		{
			if(GetStoneCount(!white, x - i, y) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x - i;
			addY[i - 1] = y;
		}
		// Right
		else if(direction == 82 || direction == 114)
		{
			if(GetStoneCount(!white, x + i, y) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x + i;
			addY[i - 1] = y;
		}
		// Northwest
		if(direction == 165 || direction == 229)
		{
			if(GetStoneCount(!white, x - i, y - i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x - i;
			addY[i - 1] = y - i;
		}
		// Northeast
		else if(direction == 147 || direction == 211)
		{
			if(GetStoneCount(!white, x + i, y - i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x + i;
			addY[i - 1] = y - i;
		}
		// Southwest
		else if(direction == 170 || direction == 234)
		{
			if(GetStoneCount(!white, x - i, y + i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x - i;
			addY[i - 1] = y + i;
		}
		// Southeast
		else if(direction == 152 || direction == 216)
		{
			if(GetStoneCount(!white, x + i, y + i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x + i;
			addY[i - 1] = y + i;
		}
	}

	// Place stones in correct spaces
	switch(freeSpaces)
	{
		case 1:
			AddStones(white, addX[0], addY[0], numStones);
			break;
		case 2:
			AddStones(white, addX[0], addY[0], 1);
			numStones--;
			if(numStones > 0) { AddStones(white, addX[1], addY[1], numStones); }
			break;
		case 3:
			AddStones(white, addX[0], addY[0], 1);
			numStones--;
			if(numStones >= 2) { AddStones(white, addX[1], addY[1], 2); }
			else { AddStones(white, addX[1], addY[1], numStones); }
			numStones -= 2;
			if(numStones > 0) { AddStones(white, addX[2], addY[2], numStones); }
			break;
	}

	// Return freeSpaces for eval function
	return freeSpaces;
}

bool Board::CheckLoss(bool white)
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
			int count = GetStoneCount(white, x, y);
			if(count <= 0)
			{
				continue;
			}
			else
			{
				for(int i = 0; i < 8; i++)
				{
					if(CheckInput(white, x, y, directions[i]) == true)
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}

std::vector<Move> Board::GetMoves(bool white)
{
	return GetMoves(white ? "White" : "Black");
}

bool Board::operator==(Board board)
{
	for(auto y = 0; y < 4; y++)
	{
		for(auto x = 0; x < 4; x++)
		{
			if(this->whiteStoneCounts[x][y] != board.whiteStoneCounts[x][y])
			{
				return false;
			}
			if(this->blackStoneCounts[x][y] != board.blackStoneCounts[x][y])
			{
				return false;
			}
		}
	}

	return true;
}
