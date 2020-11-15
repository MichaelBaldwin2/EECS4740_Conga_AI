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
	/*Texture boardTexture;
	Texture blackStoneTexture;
	Texture whiteStoneTexture;*/
	Agent* blackPlayer;
	Agent* whitePlayer;
	//Texture arialFontTexture;
	int updateFPS;
	int renderFPS;
	int totalMoves;
	float timeTaken;
	bool pauseSim;
	/*Texture pauseButtonTexture;
	Texture playButtonTexture;
	Texture stepButtonTexture;
	Texture resetButtonTexture;*/

public:
	Game();
	~Game();
	bool Init();
	void Loop();
	void UpdateTick(float deltaTime);
	void RenderTick(float deltaTime);
	Board* GetBoard();
};
