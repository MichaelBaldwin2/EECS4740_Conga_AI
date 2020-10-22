#include "Board.h"
#include <iostream>
#include <sstream>
#include <vector>

Board::Board(unsigned int boardWidth, unsigned int boardHeight) : boardWidth(boardWidth), boardHeight(boardHeight), whiteStoneCounts(boardWidth * boardHeight, 0), blackStoneCounts(boardWidth* boardHeight, 0) {}

int Board::GetStoneCount(bool white, unsigned int x, unsigned int y)
{
	if(CheckBounds(x, y))
	{
		std::cout << "GetStoneCount(): Grid location is out of bounds" << std::endl;
		return -1;
	}

	return white ? whiteStoneCounts[y * boardWidth + x] : blackStoneCounts[y * boardWidth + x];
}

int Board::AddStones(bool white, unsigned int x, unsigned int y, unsigned int count)
{
	if(CheckBounds(x, y))
	{
		std::cout << "AddStones(): Grid location is out of bounds" << std::endl;
		return -1;
	}

	white ? whiteStoneCounts[y * boardWidth + x] += count : blackStoneCounts[y * boardWidth + x] += count;
	return GetStoneCount(white, x, y);
}

int Board::RemoveStones(bool white, unsigned int x, unsigned int y)
{
	if(CheckBounds(x, y))
	{
		std::cout << "RemoveStones(): Grid location is out of bounds" << std::endl;
		return -1;
	}

	auto stoneCount = GetStoneCount(white, x, y);
	white ? whiteStoneCounts[y * boardWidth + x] = 0 : blackStoneCounts[y * boardWidth + x] = 0;
	return stoneCount;
}

void Board::PrintBoardToConsole()
{
	for(auto y = 0; y < boardHeight; y++)
	{
		//auto stringBuilder = std::stringstream();
		std::cout << "|";
		for(auto x = 0; x < boardWidth; x++)
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
	return x >= boardWidth || y >= boardHeight;
}
