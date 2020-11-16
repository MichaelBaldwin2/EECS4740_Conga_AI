/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

/// <summary>
/// Represents a possible move on the Conga board.
/// Has an x and y (cell location) and a movement direction (0-7 inclusive)
/// </summary>
struct Move
{
	int x, y;
	int direction;
};