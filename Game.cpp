#include "Board.h"
#include "Game.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "RectInt.h"
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
int totalMoves = 0;

Game::Game() : board(), isRunning(true), window(), renderer(), spriteBatch(), boardTexture(), blackStoneTexture(), whiteStoneTexture(), blackPlayer(new RandomPlayer()), whitePlayer(new AIPlayer()), arialFontTexture(), arialFont(), updateFPS(), renderFPS(), playButton(), pauseButton(), stepButton(), pauseSim(true) {}

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
	playButton = Texture(renderer, "Play_Button.png");
	pauseButton = Texture(renderer, "Pause_Button.png");
	stepButton = Texture(renderer, "Step_Button.png");
	resetButton = Texture(renderer, "Reset_Button.png");

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
	bool singleStep = false;

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			isRunning = false;
		}
		if(e.type == SDL_MOUSEBUTTONUP)
		{
			mb = e.button;

			// We need to check the buttons
			if(RectInt(656, 0, 64, 64).IsWithin(Vector2Int(e.button.x, e.button.y)))
			{
				spdlog::info("Pause button was pressed!");
				pauseSim = true;
			}
			if(RectInt(720, 0, 64, 64).IsWithin(Vector2Int(e.button.x, e.button.y)))
			{
				spdlog::info("Play button was pressed!");
				pauseSim = false;
			}
			if(RectInt(784, 0, 64, 64).IsWithin(Vector2Int(e.button.x, e.button.y)))
			{
				spdlog::info("Step button was pressed!");
				pauseSim = true;
				singleStep = true;
			}
			if(RectInt(848, 0, 64, 64).IsWithin(Vector2Int(e.button.x, e.button.y)))
			{
				spdlog::info("Reset button was pressed!");
				pauseSim = true;
				board = Board();
				board.AddStones(false, 0, 0, 10);
				board.AddStones(true, 3, 3, 10);

				// Set player names and start player
				delete whitePlayer;
				delete blackPlayer;
				blackPlayer = new RandomPlayer();
				whitePlayer = new AIPlayer();
				blackPlayer->name = "Black";
				whitePlayer->name = "White";
				player = blackPlayer;
				totalMoves = 0;
			}
		}
	}

	if(pauseSim == false || singleStep == true)
	{
		// Check if current player lost
		if(board.CheckLoss((player == whitePlayer)))
		{
			std::cout << player->name << " has lost." << std::endl;
			isRunning = false;
		}

		// Get and make next move
		auto nextMove = player->GetMove(board, mb);

		if(board.CheckInput((player == whitePlayer), nextMove.x, nextMove.y, nextMove.direction))
		{
			// Move stones and print board
			board.MoveStones(player == whitePlayer, nextMove.x, nextMove.y, nextMove.direction);
			totalMoves++;
			std::cout << "Total Moves: " << totalMoves << std::endl;

			// Change current player
			switch(player == blackPlayer)
			{
				case false:
					player = blackPlayer;
					break;
				case true:
					player = whitePlayer;
					break;
			}

			singleStep = false;
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

	//Render Pause, Play, and Step buttons
	spriteBatch.Draw(pauseButton, Vector2(656, 0));
	spriteBatch.Draw(playButton, Vector2(720, 0));
	spriteBatch.Draw(stepButton, Vector2(784, 0));
	spriteBatch.Draw(resetButton, Vector2(848, 0));

	// Render FPS and UPS
	spriteBatch.DrawString("FPS:" + std::to_string(renderFPS), arialFont, Vector2::Zero);
	spriteBatch.DrawString("UPS:" + std::to_string(updateFPS), arialFont, Vector2(0, 16));

	spriteBatch.End();
	renderer.PresentScreen();
}

Board* Game::GetBoard()
{
	return &board;
}