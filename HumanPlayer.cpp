/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "HumanPlayer.h"
#include "RectInt.h"
#include <string>
#include <random>
#include <iostream>

struct CellPos
{
	RectInt rect;
	Vector2Int cell;
};

HumanPlayer::HumanPlayer() : selectedCell(-1, -1) {}

Move HumanPlayer::GetMove(Board board, SDL_MouseButtonEvent& mb)
{
	CellPos cells[] = {
		// Top Row (left-right)
		{ RectInt(48, 48, 127, 127), Vector2Int(0, 0) },
		{ RectInt(192, 48, 127, 127), Vector2Int(1, 0) },
		{ RectInt(336, 48, 127, 127), Vector2Int(2, 0) },
		{ RectInt(480, 48, 127, 127), Vector2Int(3, 0) },

		// 2nd Row (left-right)
		{ RectInt(48, 192, 127, 127), Vector2Int(0, 1) },
		{ RectInt(192, 192, 127, 127), Vector2Int(1, 1) },
		{ RectInt(336, 192, 127, 127), Vector2Int(2, 1) },
		{ RectInt(480, 192, 127, 127), Vector2Int(3, 1) },

		// 3rd Row (left-right)
		{ RectInt(48, 336, 127, 127), Vector2Int(0, 2) },
		{ RectInt(192, 336, 127, 127), Vector2Int(1, 2) },
		{ RectInt(336, 336, 127, 127), Vector2Int(2, 2) },
		{ RectInt(480, 336, 127, 127), Vector2Int(3, 2) },

		// 4th Row (left-right)
		{ RectInt(48, 480, 127, 127), Vector2Int(0, 3) },
		{ RectInt(192, 480, 127, 127), Vector2Int(1, 3) },
		{ RectInt(336, 480, 127, 127), Vector2Int(2, 3) },
		{ RectInt(480, 480, 127, 127), Vector2Int(3, 3) }
	};

	auto move = Move{0, 0, -1};

	// Means we haven't selected a cell yet
	if(selectedCell.x == -1 || selectedCell.y == -1)
	{
		// Check if the event was a left click
		if(mb.type == SDL_MOUSEBUTTONUP && mb.button == SDL_BUTTON_LEFT)
		{
			auto mousePos = Vector2Int(mb.x, mb.y);
			
			for(int i = 0; i < 16; i++)
			{
				if(cells[i].rect.ContainsPoint(mousePos))
				{
					selectedCell = cells[i].cell;
					std::cout << "Cell " << selectedCell.x << ", " << selectedCell.y << " selected" << std::endl;
				}
			}
		}
	}
	else // If we have selected a cell already
	{
		auto moveToCell = Vector2Int(-1, -1);

		// Check if the event was a left click
		if(mb.type == SDL_MOUSEBUTTONUP && mb.button == SDL_BUTTON_LEFT)
		{
			auto mousePos = Vector2Int(mb.x, mb.y);

			for(int i = 0; i < 16; i++)
			{
				if(cells[i].rect.ContainsPoint(mousePos))
				{
					moveToCell = cells[i].cell;
					std::cout << "MovedToCell " << moveToCell.x << ", " << moveToCell.y << " selected" << std::endl;
				}
			}
		}

		// If we selected a moveToCell
		if(moveToCell.x != -1 && moveToCell.y != -1)
		{
			if(moveToCell.x < selectedCell.x)
			{
				if(moveToCell.y < selectedCell.y)
				{
					move.direction = 165; // NW
				}
				else if(moveToCell.y > selectedCell.y)
				{
					move.direction = 170; // SW
				}
				else
				{
					move.direction = 76; // L
				}
			}
			else if(moveToCell.x > selectedCell.x)
			{
				if(moveToCell.y < selectedCell.y)
				{
					move.direction = 147; // NE
				}
				else if(moveToCell.y > selectedCell.y)
				{
					move.direction = 152; // SE
				}
				else
				{
					move.direction = 82; // R
				}
			}
			else
			{
				if(moveToCell.y < selectedCell.y)
				{
					move.direction = 85; // U
				}
				else if(moveToCell.y > selectedCell.y)
				{
					move.direction = 68; // D
				}
				else
				{
					move.direction = -1; // POOPIE MOVE
				}
			}

			move.x = selectedCell.x;
			move.y = selectedCell.y;
			selectedCell = Vector2Int(-1, -1);
		}
	}

	// Clear selectedCell on right click
	if(mb.type == SDL_MOUSEBUTTONUP && mb.button == SDL_BUTTON_RIGHT)
	{
		selectedCell = Vector2Int(-1, -1);
		std::cout << "Selected cell cleared" << std::endl;
	}

	return move;
}
