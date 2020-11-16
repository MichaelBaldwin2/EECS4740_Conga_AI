/*
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
	Game();
	~Game();
	bool Init();
	void Loop();
	void UpdateTick(float deltaTime);
	void RenderTick(float deltaTime);
};
