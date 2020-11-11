#include "Board.h"
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

int Board::GetStoneCount(bool white, unsigned int x, unsigned int y)
{
	if(CheckBounds(x, y))
	{
		//std::cout << "GetStoneCount(): Grid location is out of bounds" << std::endl;
		return -1;
	}

	return white ? whiteStoneCounts[y][x] : blackStoneCounts[y][x];
}

int Board::AddStones(bool white, unsigned int x, unsigned int y, unsigned int count)
{
	if(CheckBounds(x, y))
	{
		//std::cout << "AddStones(): Grid location is out of bounds" << std::endl;
		return -1;
	}

	white ? whiteStoneCounts[y][x] += count : blackStoneCounts[y][x] += count;
	return GetStoneCount(white, x, y);
}

int Board::RemoveStones(bool white, unsigned int x, unsigned int y)
{
	if(CheckBounds(x, y))
	{
		//std::cout << "RemoveStones(): Grid location is out of bounds" << std::endl;
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
		//auto stringBuilder = std::stringstream();
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

			//std::cout << "| " << (whiteCount < 10 ? "0" : "") << whiteCount << "-" << (blackCount < 10 ? "0" : "") << blackCount << " |";
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

	if (x < 0 || x > 3)
	{
		std::cout << "ERROR: Please enter a valid x coordinate." << std::endl;
		return false;
	}
	if (y < 0 || y > 3)
	{
		std::cout << "ERROR: Please enter a valid y coordinate." << std::endl;
		return false;
	}
	if (std::find(std::begin(validDirections), std::end(validDirections), direction) == std::end(validDirections))
	{
		std::cout << "ERROR: Please enter a valid direction." << std::endl;
		return false;
	}
	if (GetStoneCount(white, x, y) == 0)
	{
		return false;
	}
	// Up
	if (direction == 85 || direction == 117)
	{
		return (GetStoneCount(!white, x, y - 1) == 0);
	}
	// Down
	else if (direction == 68 || direction == 100)
	{
		return (GetStoneCount(!white, x, y + 1) == 0);
	}
	// Left
	else if (direction == 76 || direction == 108)
	{
		return (GetStoneCount(!white, x - 1, y) == 0);
	}
	// Right
	else if (direction == 82 || direction == 114)
	{
		return (GetStoneCount(!white, x + 1, y) == 0);
	}
	// Northwest
	else if (direction == 165 || direction == 229)
	{
		return (GetStoneCount(!white, x - 1, y - 1) == 0);
	}
	// Northeast
	else if (direction == 147 || direction == 211)
	{
		return (GetStoneCount(!white, x + 1, y - 1) == 0);
	}
	// Southwest
	else if (direction == 170 || direction == 234)
	{
		return (GetStoneCount(!white, x - 1, y + 1) == 0);
	}
	// Southeast
	else if (direction == 152 || direction == 216)
	{
		return (GetStoneCount(!white, x + 1, y + 1) == 0);
	}
	else
	{
		return false;
	}
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

