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
#include <typeinfo>

Agent* player;

Game::Game() : board(), isRunning(true), window(), renderer(), spriteBatch(), boardTexture(), blackStoneTexture(), whiteStoneTexture(), blackPlayer(new RandomPlayer()), whitePlayer(new AIPlayer()), arialFontTexture(), arialFont(), updateFPS(), renderFPS() {}

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
	arialFontTexture = Texture(renderer, "Arial.png");
	arialFont = SpriteFont(arialFontTexture, 16, 16, 256);

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
	int upsCount = 0;
	int fpsCount = 0;
	float delay = 0.1f;
	if(typeid(*blackPlayer) == typeid(HumanPlayer))
	{
		delay = 0.016f;
	}

	while(isRunning)
	{
		if(Time::RealTimeSinceStartup() >= nextUpdate)
		{
			nextUpdate = Time::RealTimeSinceStartup() + delay;
			Time::UpdateLogicDeltaTime();
			UpdateTick(Time::LogicDeltaTime());
			upsCount++;
		}

		Time::UpdateRenderDeltaTime();
		RenderTick(Time::RenderDeltaTime());
		fpsCount++;

		// Render the fps to the console
		if(Time::RealTimeSinceStartup() >= nextFpsRender)
		{
			nextFpsRender = Time::RealTimeSinceStartup() + 1.0f;
			spdlog::info("FPS: {0}({1:.4f}):{2}({3:.4f})", updateFPS, Time::LogicDeltaTime(), renderFPS, Time::RenderDeltaTime());
			updateFPS = upsCount;
			renderFPS = fpsCount;
			upsCount = 0;
			fpsCount = 0;
		}
	}
}

void Game::UpdateTick(float deltaTime)
{
	SDL_Event e;
	SDL_MouseButtonEvent mb;

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			isRunning = false;
		}
		if(e.type == SDL_MOUSEBUTTONUP)
		{
			mb = e.button;
		}
	}

	// Check if current player lost
	if(board.CheckLoss((player == whitePlayer))) {
		std::cout << player->name << " has lost." << std::endl;
		isRunning = false;
	}

	// Get and make next move
	auto nextMove = player->GetMove(board, mb);

	if (board.CheckInput((player == whitePlayer), nextMove.x, nextMove.y, nextMove.direction))
	{
		// Move stones and print board
		board.MoveStones(player == whitePlayer, nextMove.x, nextMove.y, nextMove.direction);
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
	spriteBatch.Draw(Sprite(boardTexture), Vector2::Zero, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.5f);

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
					spriteBatch.Draw(Sprite(whiteStoneTexture), position, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.25f);
				}
			}
			for(int drawY = 0, i = 0; drawY < 64 && i < blackStoneCount; drawY += 16)
			{
				for(auto drawX = 0; drawX < 64 && i < blackStoneCount; drawX += 16, i++)
				{
					auto position = Vector2((75 + (x * 144)) + drawX, (75 + (y * 144)) + drawY);
					spriteBatch.Draw(Sprite(blackStoneTexture), position, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.25f);
				}
			}
		}
	}

	// Render the GUI
	spriteBatch.DrawString("FPS:" + std::to_string(renderFPS), arialFont, Vector2::Zero);
	spriteBatch.DrawString("UPS:" + std::to_string(updateFPS), arialFont, Vector2(0, 16));

	spriteBatch.End();
	renderer.PresentScreen();
}

Board* Game::GetBoard()
{
	return &board;
}