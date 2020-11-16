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

class HumanPlayer : public Agent
{
private:
	Vector2Int selectedCell;

public:
	HumanPlayer();
	Move GetMove(Board board, SDL_MouseButtonEvent& mb);
};
