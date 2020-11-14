#pragma once

#include "Agent.h"
#include "Board.h"
#include "Renderer.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "Window.h"

class Game
{
private:
	Board board;
	bool isRunning;
	Window window;
	Renderer renderer;
	SpriteBatch spriteBatch;
	Texture boardTexture;
	Texture blackStoneTexture;
	Texture whiteStoneTexture;
	Agent* blackPlayer;
	Agent* whitePlayer;
	Texture arialFontTexture;
	SpriteFont arialFont;
	int updateFPS;
	int renderFPS;
	Texture playButton;
	Texture pauseButton;
	Texture stepButton;
	Texture resetButton;
	bool pauseSim;

public:
	Game();
	~Game();
	bool Init();
	void Loop();
	void UpdateTick(float deltaTime);
	void RenderTick(float deltaTime);
	Board* GetBoard();
};
