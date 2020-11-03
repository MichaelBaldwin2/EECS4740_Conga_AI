#pragma once

#include "Board.h"
#include "Renderer.h"
#include "Texture.h"
#include "SpriteBatch.h"
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
	int currentPlayer;

public:
	Game();
	~Game();
	bool Init();
	void Loop();
	void UpdateTick(float deltaTime);
	void RenderTick(float deltaTime);
	Board* GetBoard();

private:
	bool CheckLoss();
	bool CheckInput(int x, int y, int direction);
	void MoveStones(int x, int y, int direction);
};

