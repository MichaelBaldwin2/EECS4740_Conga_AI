/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include "Agent.h"
#include "Vector2Int.h"

/// <summary>
/// Human playable agent. Uses the mouse to point and click moves.
/// </summary>
class HumanPlayer : public Agent
{
private:
	Vector2Int selectedCell;

public:
	/// <summary>
	/// Constructor
	/// </summary>
	HumanPlayer();
	Move GetMove(Board board, SDL_MouseButtonEvent& mb);
};
