/* Game.h
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include "Agent.h"
#include "Board.h"
#include "Button.h"
#include "Renderer.h"
#include "Texture.h"
#include "TTFFont.h"
#include "SpriteBatch.h"
#include "Window.h"
#include <map>
#include <string>

/// <summary>
/// Main game class. Runs the loop and all required information for the game to run.
/// </summary>
class Game
{
private:
	Board board;
	bool isRunning;
	Window window;
	Renderer renderer;
	SpriteBatch spriteBatch;
	std::map<std::string, Texture> textures;
	TTFFont arialFontSmall;
	TTFFont arialFontNormal;
	TTFFont arialFontLarge;
	Button pauseButton;
	Button playButton;
	Button stepButton;
	Button resetButton;
	Agent* blackPlayer;
	Agent* whitePlayer;
	int updateFPS;
	int renderFPS;
	bool pauseSim;
	int totalMoves;
	float timeTaken;
	float timeTakenAvg;
	float timeTakenCount;
	float timeTakenTotal;
	std::string onLossText;

public:
	/// <summary>
	/// Constructor
	/// </summary>
	Game();
	/// <summary>
	/// Explicit destructor so that we can release gpu held resources before subsystem shutdown
	/// </summary>
	~Game();
	/// <summary>
	/// Loads all textures, fonts, the game board, and the players
	/// </summary>
	bool Init();
	/// <summary>
	/// Main loop
	/// </summary>
	void Loop();
	/// <summary>
	/// Logic update loop
	/// </summary>
	/// <param name="deltaTime">Amount of time in seconds that have passed since this function was called last</param>
	void UpdateTick(float deltaTime);
	/// <summary>
	/// Render update loop
	/// </summary>
	/// <param name="deltaTime">Amount of time in seconds that have passed since this function was called last</param>
	void RenderTick(float deltaTime);
};
