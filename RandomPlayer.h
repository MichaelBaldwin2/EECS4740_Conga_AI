/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include "Agent.h"
#include <random>

/// <summary>
/// Random Agent
/// Uses a Mersenne Twister pseudo-random number generator to pick moves from two uniform distributions.
/// Seeded in the constructor.
/// </summary>
class RandomPlayer : public Agent
{
private:
	std::mt19937 random;

public:
	/// <summary>
	/// Constructor, seeds random number generator.
	/// </summary>
	RandomPlayer();
	Move GetMove(Board board, SDL_MouseButtonEvent& mb);
};
