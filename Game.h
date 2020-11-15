#pragma once

#include "Agent.h"
#include "Board.h"
#include "Button.h"
#include "Renderer.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
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
	SpriteFont arialFont;
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
	std::string onLossText;

public:
	Game();
	~Game();
	bool Init();
	void Loop();
	void UpdateTick(float deltaTime);
	void RenderTick(float deltaTime);
};
