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
#include <SDL.h>
#include <string>

/// <summary>
/// Abstract base class for all playable agents in game (HumanPlayer, RandomPlayer, and AIPlayer)
/// </summary>
class Agent
{
public:
	/// <summary>
	/// The name of the player (White or Black)
	/// </summary>
	std::string name;

public:
	/// <summary>
	/// Called when a move is requested from the agent, specifications left up to the agent.
	/// </summary>
	/// <param name="board">The board that the move will be used on</param>
	/// <param name="mb">An SDL_MouseButtonEvent structure (only used with HumanPlayer)</param>
	/// <returns>A filled Move structure</returns>
	virtual Move GetMove(Board board, SDL_MouseButtonEvent &mb) = 0;
};
