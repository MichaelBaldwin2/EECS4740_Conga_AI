#pragma once

#include <string>
#include <vector>

class Board
{
private:
	unsigned int whiteStoneCounts[4][4];
	unsigned int blackStoneCounts[4][4];

public:
	Board();

	int GetStoneCount(const char* player, unsigned int x, unsigned int y) { return GetStoneCount(std::string(player), x, y); };
	int AddStones(const char* player, unsigned int x, unsigned int y, unsigned int count) { return AddStones(std::string(player), x, y, count); };
	int RemoveStones(const char* player, unsigned int x, unsigned int y) { return RemoveStones(std::string(player), x, y); };
	bool CheckInput(const char* player, int x, int y, int direction) { return CheckInput(std::string(player), x, y, direction); };
	int MoveStones(const char* player, unsigned int x, unsigned int y, unsigned int direction) { return MoveStones(std::string(player), x, y, direction); };
	bool CheckLoss(const char* player) { return CheckLoss(std::string(player)); };

	int GetStoneCount(std::string player, unsigned int x, unsigned int y) { return GetStoneCount(player.compare("White"), x, y); };
	int AddStones(std::string player, unsigned int x, unsigned int y, unsigned int count) { return AddStones(player.compare("White"), x, y, count); };
	int RemoveStones(std::string player, unsigned int x, unsigned int y) { return RemoveStones(player.compare("White"), x, y); };
	bool CheckInput(std::string player, int x, int y, int direction) { return CheckInput(player.compare("White"), x, y, direction); };
	int MoveStones(std::string player, unsigned int x, unsigned int y, unsigned int direction) { return MoveStones(player.compare("White"), x, y, direction); };
	bool CheckLoss(std::string player) { return CheckLoss(player.compare("White")); };

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
