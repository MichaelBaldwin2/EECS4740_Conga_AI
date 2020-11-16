/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include "Board.h"
#include "Move.h"

/// <summary>
/// Represents a current state of a board.
/// Contains a Board instance (very very small at 256 bytes)
/// A Move structure (basically what the move on this board was)
/// An evaluation value
/// </summary>
struct BoardState
{
	Board board;
	Move move;
	int evalValue;
};
