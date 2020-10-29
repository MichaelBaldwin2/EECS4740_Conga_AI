#include "Board.h"
#include "Game.h"
#include "Renderer.h"
#include "Time.h"
#include "Window.h"
#include <SDL.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <string>
//#include <SDL.h>

Game::Game() : board(), isRunning(true), window(), renderer(), spriteBatch(), boardTexture(), blackStoneTexture(), whiteStoneTexture(), currentPlayer(0) {}

Game::~Game()
{
	boardTexture.Free();
	blackStoneTexture.Free();
	whiteStoneTexture.Free();
	renderer.Free();
	window.Free();
}

bool Game::Init()
{
	window = Window(1280, 720, "The Journey Home");
	if(window.GetSDLWindow() == nullptr)
	{
		return false;
	}

	renderer = Renderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer.GetSDLRenderer() == nullptr)
	{
		return false;
	}

	spriteBatch = SpriteBatch(renderer);

	// Load up the board, stones, and font textures
	boardTexture = Texture(renderer, "Board.png");
	blackStoneTexture = Texture(renderer, "BlackStone.png");
	whiteStoneTexture = Texture(renderer, "WhiteStone.png");

	board = Board(&Sprite(boardTexture));
	board.AddStones(false, 0, 0, 10);
	board.AddStones(true, 3, 3, 10);

	return true;
}

void Game::Loop()
{
	Time::UpdateLogicDeltaTime();
	Time::UpdateRenderDeltaTime();
	float nextUpdate = Time::RealTimeSinceStartup();
	float nextFpsRender = Time::RealTimeSinceStartup();
	int updateFPS = 0;
	int renderFPS = 0;

	while(isRunning)
	{
		if(Time::RealTimeSinceStartup() >= nextUpdate)
		{
			nextUpdate = Time::RealTimeSinceStartup() + 0.016f;
			Time::UpdateLogicDeltaTime();
			UpdateTick(Time::LogicDeltaTime());
			updateFPS++;
		}

		Time::UpdateRenderDeltaTime();
		RenderTick(Time::RenderDeltaTime());
		renderFPS++;

		if(Time::RealTimeSinceStartup() >= nextFpsRender)
		{
			nextFpsRender = Time::RealTimeSinceStartup() + 1.0f;
			spdlog::info("FPS: {0}({1:.4f}):{2}({3:.4f})", updateFPS, Time::LogicDeltaTime(), renderFPS, Time::RenderDeltaTime());
			updateFPS = 0;
			renderFPS = 0;
		}
	}
}

void Game::UpdateTick(float deltaTime)
{
	SDL_Event e;
	int x, y, direction;
	std::string nextMove, currentPlayerName;

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}


	// TODO: ADD DIAGONAL DIRECTIONS -- FUCK
	/* CONSOLE INPUT
	*	Input should be of the form "xyd" where:
	*	- x is the x coordinate of the pieces to move
	*	- y is the y coordinate of the pieces to move
	*	- d is the direction to move the pieces (UDLR)
	*/
	currentPlayerName = (currentPlayer == 0) ? "Black" : "White";
	std::cout << "Enter move for " << currentPlayerName << ": ";
	std::cin >> nextMove;
	if(nextMove[0] == 'q' || nextMove[0] == 'Q')
	{
		isRunning = false;
	}
	else if(nextMove.length() != 3)
	{
		std::cout << "ERROR: Please enter a valid command." << std::endl;
	}
	else
	{
		// Parse and check input
		x = nextMove[0] - 48;
		y = nextMove[1] - 48;
		direction = nextMove[2];
		if(Game::CheckInput(x, y, direction) == 0)
		{
			// Move stones and print board
			Game::MoveStones(x, y, direction);
			board.PrintBoardToConsole();

			// Change currentPlayer
			switch(currentPlayer)
			{
				case 0:
					currentPlayer = 1;
					break;
				case 1:
					currentPlayer = 0;
					break;
			}
		}
	}
	// Win condition checking

	// Rendering
}

void Game::RenderTick(float deltaTime)
{
	renderer.ClearScreen(Color::Black);
	spriteBatch.Begin();

	// All the sprite rendering happens here
	spriteBatch.Draw(board.GetSprite(), Vector2::Zero, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.25f);

	// Draw the stones
	for(auto y = 0; y < 4; y++)
	{
		for(auto x = 0; x < 4; x++)
		{
			auto whiteStoneCount = board.GetStoneCount(true, x, y);
			auto blackStoneCount = board.GetStoneCount(false, x, y);

			for(auto i = 0; i < whiteStoneCount; i++)
			{
				auto flipType = std::rand() % 3;
				auto spriteFlip = flipType == 0 ? SpriteFlip::None : flipType == 1 ? SpriteFlip::Horizontal : SpriteFlip::Vertical;
				auto position = Vector2((75 + (x * 144)) + (std::rand() % 64), (75 + (y * 144)) + (std::rand() % 64));
				spriteBatch.Draw(Sprite(whiteStoneTexture), position, Color::White, 0, Vector2::Zero, Vector2::One, spriteFlip, 0.5f);
			}
			for(auto i = 0; i < blackStoneCount; i++)
			{
				auto flipType = std::rand() % 3;
				auto spriteFlip = flipType == 0 ? SpriteFlip::None : flipType == 1 ? SpriteFlip::Horizontal : SpriteFlip::Vertical;
				auto position = Vector2((75 + (x * 144)) + (std::rand() % 64), (75 + (y * 144)) + (std::rand() % 64));
				spriteBatch.Draw(Sprite(blackStoneTexture), position, Color::White, 0, Vector2::Zero, Vector2::One, spriteFlip, 0.5f);
			}
		}
	}

	spriteBatch.End();
	renderer.PresentScreen();
}

Board* Game::GetBoard()
{
	return &board;
}

int Game::CheckInput(int x, int y, int direction) {
	/*
	* Up:		85 or 117
	* Down:		68 or 100
	* Left:		76 or 108
	* Right:	82 or 114
	*/
	const int validDirections[] = { 85, 117, 68, 100, 76, 108, 82, 114, -1 };
	int errorCount = 0;
	bool white = !(currentPlayer == 0);

	if (x < 0 || x > 3) {
		std::cout << "ERROR: Please enter a valid x coordinate." << std::endl;
		errorCount++;
	}

	if (y < 0 || y > 3) {
		std::cout << "ERROR: Please enter a valid y coordinate." << std::endl;
		errorCount++;
	}

	if (std::find(std::begin(validDirections), std::end(validDirections), direction) == std::end(validDirections)) {
		std::cout << "ERROR: Please enter a valid direction." << std::endl;
		errorCount++;
	}

	if (board.GetStoneCount(white, x, y) == 0) {
		std::cout << "ERROR: Must select current player's stones." << std::endl;
		errorCount++;
	}

	errorCount += Game::CheckInputDirection(x, y, direction);

	return errorCount;
}

int Game::CheckInputDirection(int x, int y, int direction) {
	bool white = !(currentPlayer == 0);
	int validDirectionTest = -1;

	// Up
	if (direction == 85 || direction == 117) {
		validDirectionTest = board.GetStoneCount(!white, x, y - 1);
	}
	// Down
	else if (direction == 68 || direction == 100) {
		validDirectionTest = board.GetStoneCount(!white, x, y + 1);
	}
	// Left
	else if (direction == 76 || direction == 108) {
		validDirectionTest = board.GetStoneCount(!white, x - 1, y);
	}
	// Right
	else if (direction == 82 || direction == 114) {
		validDirectionTest = board.GetStoneCount(!white, x + 1, y);
	}

	switch (validDirectionTest) {
	case -1:
		return 1;
	case 0:
		break;
	default:
		std::cout << "ERROR: That space contains the other player's stones." << std::endl;
		return 1;
	}

	return 0;
}

void Game::MoveStones(int x, int y, int direction) {
	bool white = !(currentPlayer == 0);
	int numStones = board.RemoveStones(white, x, y);
	int freeSpaces = 0;

	// Up
	if (direction == 85 || direction == 117) {
		// Determine free spaces
		for (int i = 1; i < 4; i++) {
			if (board.GetStoneCount(!white, x, y - i) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
		}

		// Place stones into free spaces
		switch (freeSpaces) {
		case 1:
			board.AddStones(white, x, y - 1, numStones);
			break;
		case 2:
			board.AddStones(white, x, y - 1, 1);
			numStones--;
			if (numStones > 0) { board.AddStones(white, x, y - 2, numStones); }
			break;
		case 3:
			board.AddStones(white, x, y - 1, 1);
			numStones--;
			if (numStones >= 2) { board.AddStones(white, x, y - 2, 2); }
			else { board.AddStones(white, x, y - 2, numStones); }
			numStones -= 2;
			if (numStones > 0) { board.AddStones(white, x, y - 3, numStones); }
			break;
		}
	}
	// Down
	else if (direction == 68 || direction == 100) {
		for (int i = 1; i < 4; i++) {
			if (board.GetStoneCount(!white, x, y + i) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
		}

		// Place stones into free spaces
		switch (freeSpaces) {
		case 1:
			board.AddStones(white, x, y + 1, numStones);
			break;
		case 2:
			board.AddStones(white, x, y + 1, 1);
			numStones--;
			if (numStones > 0) { board.AddStones(white, x, y + 2, numStones); }
			break;
		case 3:
			board.AddStones(white, x, y + 1, 1);
			numStones--;
			if (numStones >= 2) { board.AddStones(white, x, y + 2, 2); }
			else { board.AddStones(white, x, y + 2, numStones); }
			numStones -= 2;
			if (numStones > 0) { board.AddStones(white, x, y + 3, numStones); }
			break;
		}
	}
	// Left
	else if (direction == 76 || direction == 108) {
		// Determine free spaces
		for (int i = 1; i < 4; i++) {
			if (board.GetStoneCount(!white, x - i, y) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
		}

		// Place stones into free spaces
		switch (freeSpaces) {
		case 1:
			board.AddStones(white, x - 1, y, numStones);
			break;
		case 2:
			board.AddStones(white, x - 1, y, 1);
			numStones--;
			if (numStones > 0) { board.AddStones(white, x - 2, y, numStones); }
			break;
		case 3:
			board.AddStones(white, x - 1, y, 1);
			numStones--;
			if (numStones >= 2) { board.AddStones(white, x - 2, y, 2); }
			else { board.AddStones(white, x - 2, y, numStones); }
			numStones -= 2;
			if (numStones > 0) { board.AddStones(white, x - 3, y, numStones); }
			break;
		}
	}
	// Right
	else if (direction == 82 || direction == 114) {
		// Determine free spaces
		for (int i = 1; i < 4; i++) {
			if (board.GetStoneCount(!white, x + i, y) == 0) {
				freeSpaces++;
			}
			else {
				break;
			}
		}

		// Place stones into free spaces
		switch (freeSpaces) {
		case 1:
			board.AddStones(white, x + 1, y, numStones);
			break;
		case 2:
			board.AddStones(white, x + 1, y, 1);
			numStones--;
			if (numStones > 0) { board.AddStones(white, x + 2, y, numStones); }
			break;
		case 3:
			board.AddStones(white, x + 1, y, 1);
			numStones--;
			if (numStones >= 2) { board.AddStones(white, x + 2, y, 2); }
			else { board.AddStones(white, x + 2, y, numStones); }
			numStones -= 2;
			if (numStones > 0) { board.AddStones(white, x + 3, y, numStones); }
			break;
		}
	}
}
