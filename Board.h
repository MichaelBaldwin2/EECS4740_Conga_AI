/* Board.h
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include "Move.h"
#include <string>
#include <vector>

/// <summary>
/// Represents a game board
/// </summary>
class Board
{
private:
	int whiteStoneCounts[4][4];
	int blackStoneCounts[4][4];

public:
	Board();

	/// <summary>
	/// Gets the stone count at a grid cell froma  specific player color
	/// </summary>
	int GetStoneCount(const char* player, unsigned int x, unsigned int y);
	/// <summary>
	/// Adds player stones to a grid cell
	/// </summary>
	int AddStones(const char* player, unsigned int x, unsigned int y, unsigned int count);
	/// <summary>
	/// Removes all player stones from a grid cell
	/// </summary>
	int RemoveStones(const char* player, unsigned int x, unsigned int y);
	/// <summary>
	/// Determines if a specified player input is allowed on thsi game board
	/// </summary>
	bool CheckInput(const char* player, int x, int y, int direction);
	/// <summary>
	/// Performs a movement of player stones from a specific cell in a specified direction
	/// </summary>
	int MoveStones(const char* player, unsigned int x, unsigned int y, unsigned int direction);
	/// <summary>
	/// Determines if a player has lost (aka has no moves available to them)
	/// </summary>
	bool CheckLoss(const char* player);
	/// <summary>
	/// Returns a list of moves that a player has on thsi board
	/// </summary>
	std::vector<Move> GetMoves(const char* player);

	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	int GetStoneCount(std::string player, unsigned int x, unsigned int y);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	int AddStones(std::string player, unsigned int x, unsigned int y, unsigned int count);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	int RemoveStones(std::string player, unsigned int x, unsigned int y);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	bool CheckInput(std::string player, int x, int y, int direction);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	int MoveStones(std::string player, unsigned int x, unsigned int y, unsigned int direction);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	bool CheckLoss(std::string player);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	std::vector<Move> GetMoves(std::string player);

	/// <summary>
	/// Prints the board to console, not used with the GUI version.
	/// </summary>
	void PrintBoardToConsole();
	/// <summary>
	/// Compars board cells to determine if the boards are the same
	/// </summary>
	bool operator ==(Board board);

private:
	int GetStoneCount(bool white, unsigned int x, unsigned int y);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	int AddStones(bool white, unsigned int x, unsigned int y, unsigned int count);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	int RemoveStones(bool white, unsigned int x, unsigned int y);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	bool CheckInput(bool white, int x, int y, int direction);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	int MoveStones(bool white, unsigned int x, unsigned int y, unsigned int direction);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	bool CheckLoss(bool white);
	/// <summary>
	/// Overload function, just calls it's equivilent with different parameters
	/// </summary>
	std::vector<Move> GetMoves(bool white);

private:
	/// <summary>
	/// Determines if a grid cell is actually on the board, jsut a helper function
	/// </summary>
	bool CheckBounds(unsigned int x, unsigned int y);
};
