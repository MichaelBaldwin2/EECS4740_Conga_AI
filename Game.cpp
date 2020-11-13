#include "Board.h"
#include "Game.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Renderer.h"
#include "Time.h"
#include "Window.h"
#include "Agent.h"
#include <SDL.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <string>

Agent* player;

Game::Game() : board(), isRunning(true), window(), renderer(), spriteBatch(), boardTexture(), blackStoneTexture(), whiteStoneTexture(), blackPlayer(new HumanPlayer()), whitePlayer(new AIPlayer()) {}

Game::~Game()
{
	delete whitePlayer;
	delete blackPlayer;
	boardTexture.Free();
	blackStoneTexture.Free();
	whiteStoneTexture.Free();
	renderer.Free();
	window.Free();
}

bool Game::Init()
{
	window = Window(1280, 720, "Conga AI");
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

	// Initialize board and add starting stones
	board = Board();
	board.AddStones(false, 0, 0, 10);
	board.AddStones(true, 3, 3, 10);

	// Set player names and start player
	blackPlayer->name = "Black";
	whitePlayer->name = "White";
	player = blackPlayer;

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
			nextUpdate = Time::RealTimeSinceStartup() + 1.0f;
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
	Move nextMove = Move();

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}

	// Check if current player lost
	if(board.CheckLoss((player == whitePlayer))) {
		std::cout << player->name << " has lost." << std::endl;
		exit(0);
	}

	// Get and make next move
	nextMove = player->GetMove(board);

	if (Game::CheckInput(nextMove.x, nextMove.y, nextMove.direction))
	{
		// Move stones and print board
		Game::MoveStones(nextMove.x, nextMove.y, nextMove.direction);
		board.PrintBoardToConsole();

		// Change current player
		switch (player == blackPlayer)
		{
		case false:
			player = blackPlayer;
			break;
		case true:
			player = whitePlayer;
			break;
		}
	}
}

void Game::RenderTick(float deltaTime)
{
	renderer.ClearScreen(Color::Black);
	spriteBatch.Begin();

	// All the sprite rendering happens here
	spriteBatch.Draw(Sprite(boardTexture), Vector2::Zero, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.25f);

	// Draw the stones
	for(auto y = 0; y < 4; y++)
	{
		for(auto x = 0; x < 4; x++)
		{
			auto whiteStoneCount = board.GetStoneCount(true, x, y);
			auto blackStoneCount = board.GetStoneCount(false, x, y);

			for(int drawY = 0, i = 0; drawY < 64 && i < whiteStoneCount; drawY += 16)
			{
				for(auto drawX = 0; drawX < 64 && i < whiteStoneCount; drawX += 16, i++)
				{
					auto position = Vector2((75 + (x * 144)) + drawX, (75 + (y * 144)) + drawY);
					spriteBatch.Draw(Sprite(whiteStoneTexture), position, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.5f);
				}
			}
			for(int drawY = 0, i = 0; drawY < 64 && i < blackStoneCount; drawY += 16)
			{
				for(auto drawX = 0; drawX < 64 && i < blackStoneCount; drawX += 16, i++)
				{
					auto position = Vector2((75 + (x * 144)) + drawX, (75 + (y * 144)) + drawY);
					spriteBatch.Draw(Sprite(blackStoneTexture), position, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.5f);
				}
			}

			/*for(auto i = 0; i < whiteStoneCount; i++)
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
			}*/
		}
	}

	spriteBatch.End();
	renderer.PresentScreen();
}

Board* Game::GetBoard()
{
	return &board;
}

/*
bool Game::CheckLoss()
{
	const int directions[] = {
		85,		// Up
		68,		// Down
		76,		// Left
		82,		// Right
		165,	// Northwest
		147,	// Northeast
		170,	// Southwest
		152		// Southeast
	};

	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			int count = board.GetStoneCount((player == whitePlayer), x, y);
			if(count <= 0)
			{
				continue;
			}
			else
			{
				for(int i = 0; i < 8; i++)
				{
					if(board.CheckInput((player == whitePlayer), x, y, directions[i]) == true)
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}
*/

bool Game::CheckInput(int x, int y, int direction)
{
	const int validDirections[] = {
		85, 117,	// Up
		68, 100,	// Down
		76, 108,	// Left
		82, 114,	// Right
		165, 229,	// Northwest
		147, 211,	// Northeast
		170, 234,	// Southwest
		152, 216,	// Southeast
		-1
	};
	bool white = (player == whitePlayer);

	if(x < 0 || x > 3)
	{
		std::cout << "ERROR: Please enter a valid x coordinate." << std::endl;
		return false;
	}
	if(y < 0 || y > 3)
	{
		std::cout << "ERROR: Please enter a valid y coordinate." << std::endl;
		return false;
	}
	if(std::find(std::begin(validDirections), std::end(validDirections), direction) == std::end(validDirections))
	{
		std::cout << "ERROR: Please enter a valid direction." << std::endl;
		return false;
	}
	if(board.GetStoneCount(white, x, y) == 0)
	{
		std::cout << "ERROR: Must select current player's stones." << std::endl;
		return false;
	}
	// Up
	if(direction == 85 || direction == 117)
	{
		return (board.GetStoneCount(!white, x, y - 1) == 0);
	}
	// Down
	else if(direction == 68 || direction == 100)
	{
		return (board.GetStoneCount(!white, x, y + 1) == 0);
	}
	// Left
	else if(direction == 76 || direction == 108)
	{
		return (board.GetStoneCount(!white, x - 1, y) == 0);
	}
	// Right
	else if(direction == 82 || direction == 114)
	{
		return (board.GetStoneCount(!white, x + 1, y) == 0);
	}
	// Northwest
	else if(direction == 165 || direction == 229)
	{
		return (board.GetStoneCount(!white, x - 1, y - 1) == 0);
	}
	// Northeast
	else if(direction == 147 || direction == 211)
	{
		return (board.GetStoneCount(!white, x + 1, y - 1) == 0);
	}
	// Southwest
	else if(direction == 170 || direction == 234)
	{
		return (board.GetStoneCount(!white, x - 1, y + 1) == 0);
	}
	// Southeast
	else if(direction == 152 || direction == 216)
	{
		return (board.GetStoneCount(!white, x + 1, y + 1) == 0);
	}
	else
	{
		return false;
	}
}

void Game::MoveStones(int x, int y, int direction)
{
	bool white = (player == whitePlayer);
	int numStones = board.RemoveStones(white, x, y);
	int freeSpaces = 0;
	int addX[3], addY[3];

	// Determine number of free spaces
	for(int i = 1; i < 4; i++)
	{
		// Up
		if(direction == 85 || direction == 117)
		{
			if(board.GetStoneCount(!white, x, y - i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x;
			addY[i - 1] = y - i;
		}
		// Down
		else if(direction == 68 || direction == 100)
		{
			if(board.GetStoneCount(!white, x, y + i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x;
			addY[i - 1] = y + i;
		}
		// Left
		else if(direction == 76 || direction == 108)
		{
			if(board.GetStoneCount(!white, x - i, y) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x - i;
			addY[i - 1] = y;
		}
		// Right
		else if(direction == 82 || direction == 114)
		{
			if(board.GetStoneCount(!white, x + i, y) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x + i;
			addY[i - 1] = y;
		}
		// Northwest
		if(direction == 165 || direction == 229)
		{
			if(board.GetStoneCount(!white, x - i, y - i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x - i;
			addY[i - 1] = y - i;
		}
		// Northeast
		else if(direction == 147 || direction == 211)
		{
			if(board.GetStoneCount(!white, x + i, y - i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x + i;
			addY[i - 1] = y - i;
		}
		// Southwest
		else if(direction == 170 || direction == 234)
		{
			if(board.GetStoneCount(!white, x - i, y + i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x - i;
			addY[i - 1] = y + i;
		}
		// Southeast
		else if(direction == 152 || direction == 216)
		{
			if(board.GetStoneCount(!white, x + i, y + i) == 0)
			{
				freeSpaces++;
			}
			else
			{
				break;
			}
			addX[i - 1] = x + i;
			addY[i - 1] = y + i;
		}
	}

	// Place stones in correct spaces
	switch(freeSpaces)
	{
		case 1:
			board.AddStones(white, addX[0], addY[0], numStones);
			break;
		case 2:
			board.AddStones(white, addX[0], addY[0], 1);
			numStones--;
			if(numStones > 0) { board.AddStones(white, addX[1], addY[1], numStones); }
			break;
		case 3:
			board.AddStones(white, addX[0], addY[0], 1);
			numStones--;
			if(numStones >= 2) { board.AddStones(white, addX[1], addY[1], 2); }
			else { board.AddStones(white, addX[1], addY[1], numStones); }
			numStones -= 2;
			if(numStones > 0) { board.AddStones(white, addX[2], addY[2], numStones); }
			break;
	}
}
