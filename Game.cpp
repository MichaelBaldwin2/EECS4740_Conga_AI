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

Game::Game() : board(), isRunning(true), window(), renderer(), spriteBatch(), textures(), arialFont(), pauseButton(), playButton(), stepButton(), resetButton(), blackPlayer(new RandomPlayer()), whitePlayer(new AIPlayer()), updateFPS(), renderFPS(), pauseSim(true), totalMoves(0), timeTaken(0) {}

Game::~Game()
{
	delete whitePlayer;
	delete blackPlayer;

	// Clear all the textures
	for(auto it = textures.begin(); it != textures.end(); it++)
	{
		it->second.Free();
	}

	textures.clear();
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
	textures["Board"] = Texture(renderer, "gfx/Board.png");
	textures["BlackStone"] = Texture(renderer, "gfx/BlackStone.png");
	textures["WhiteStone"] = Texture(renderer, "gfx/WhiteStone.png");
	textures["Arial"] = Texture(renderer, "gfx/Arial.png");
	textures["PauseButton"] = Texture(renderer, "gfx/PauseButton.png");
	textures["PlayButton"] = Texture(renderer, "gfx/PlayButton.png");
	textures["StepButton"] = Texture(renderer, "gfx/StepButton.png");
	textures["ResetButton"] = Texture(renderer, "gfx/ResetButton.png");

	arialFont = SpriteFont(textures["Arial"], 16, 16, 256);
	pauseButton = Button(RectInt(656, 0, 64, 64), Sprite(textures["PauseButton"]), Color(128, 128, 128));
	playButton = Button(RectInt(720, 0, 64, 64), Sprite(textures["PlayButton"]), Color(128, 128, 128));
	stepButton = Button(RectInt(784, 0, 64, 64), Sprite(textures["StepButton"]), Color(128, 128, 128));
	resetButton = Button(RectInt(848, 0, 64, 64), Sprite(textures["ResetButton"]), Color(128, 128, 128));

	// Initialize board and add starting stones
	board = Board();
	board.AddStones("Black", 0, 0, 10);
	board.AddStones("White", 3, 3, 10);

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
			//spdlog::info("FPS: {0}({1:.4f}):{2}({3:.4f})", updateFPS, Time::LogicDeltaTime(), renderFPS, Time::RenderDeltaTime());
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
		if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			// We need to check the buttons
			if(pauseButton.ContainsPoint(Vector2Int(e.button.x, e.button.y)))
			{
				pauseButton.OnDown();
			}
			if(playButton.ContainsPoint(Vector2Int(e.button.x, e.button.y)))
			{
				playButton.OnDown();
			}
			if(stepButton.ContainsPoint(Vector2Int(e.button.x, e.button.y)))
			{
				stepButton.OnDown();
			}
			if(resetButton.ContainsPoint(Vector2Int(e.button.x, e.button.y)))
			{
				resetButton.OnDown();
			}
		}
		if(e.type == SDL_MOUSEBUTTONUP)
		{
			mb = e.button;

			// We need to check the buttons
			if(pauseButton.ContainsPoint(Vector2Int(e.button.x, e.button.y)))
			{
				pauseSim = true;
			}
			if(playButton.ContainsPoint(Vector2Int(e.button.x, e.button.y)))
			{
				pauseSim = false;
			}
			if(stepButton.ContainsPoint(Vector2Int(e.button.x, e.button.y)))
			{
				pauseSim = true;
				singleStep = true;
			}
			if(resetButton.ContainsPoint(Vector2Int(e.button.x, e.button.y)))
			{
				pauseSim = true;
				board = Board();
				board.AddStones("Black", 0, 0, 10);
				board.AddStones("White", 3, 3, 10);

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

			pauseButton.OnUp();
			playButton.OnUp();
			stepButton.OnUp();
			resetButton.OnUp();
		}
	}

	if(pauseSim == false || singleStep == true)
	{
		// Check if current player lost
		if(board.CheckLoss(player->name))
		{
			std::cout << player->name << " has lost." << std::endl;
			pauseSim = true;
			return;
		}

		// Get and make next move
		auto startTime = Time::RealTimeSinceStartup();
		auto nextMove = player->GetMove(board, mb);
		auto endTime = Time::RealTimeSinceStartup();
		timeTaken = endTime - startTime;

		if(board.CheckInput(player->name, nextMove.x, nextMove.y, nextMove.direction))
		{
			// Move stones and print board
			board.MoveStones(player->name, nextMove.x, nextMove.y, nextMove.direction);
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
	spriteBatch.Draw(Sprite(textures["Board"]), Vector2::Zero, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.5f);

	// Draw the stones
	for(auto y = 0; y < 4; y++)
	{
		for(auto x = 0; x < 4; x++)
		{
			auto whiteStoneCount = board.GetStoneCount("White", x, y);
			auto blackStoneCount = board.GetStoneCount("Black", x, y);

			for(int drawY = 0, i = 0; drawY < 64 && i < whiteStoneCount; drawY += 16)
			{
				for(auto drawX = 0; drawX < 64 && i < whiteStoneCount; drawX += 16, i++)
				{
					auto position = Vector2((75 + (x * 144)) + drawX, (75 + (y * 144)) + drawY);
					spriteBatch.Draw(Sprite(textures["WhiteStone"]), position, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.25f);
				}
			}
			for(int drawY = 0, i = 0; drawY < 64 && i < blackStoneCount; drawY += 16)
			{
				for(auto drawX = 0; drawX < 64 && i < blackStoneCount; drawX += 16, i++)
				{
					auto position = Vector2((75 + (x * 144)) + drawX, (75 + (y * 144)) + drawY);
					spriteBatch.Draw(Sprite(textures["BlackStone"]), position, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.25f);
				}
			}
		}
	}

	// Render the GUI

	//Render Pause, Play, Step, and Reset buttons
	pauseButton.OnRender(spriteBatch);
	playButton.OnRender(spriteBatch);
	stepButton.OnRender(spriteBatch);
	resetButton.OnRender(spriteBatch);

	// Render FPS and UPS
	spriteBatch.DrawString("FPS:" + std::to_string(renderFPS), arialFont, Vector2::Zero);
	spriteBatch.DrawString("UPS:" + std::to_string(updateFPS), arialFont, Vector2(0, 16));
	spriteBatch.DrawString("Total Moves: " + std::to_string(totalMoves), arialFont, Vector2(700, 72));
	spriteBatch.DrawString("Time Taken: " + std::to_string(timeTaken), arialFont, Vector2(700, 88));

	//blackPlayer->OnRender(spriteBatch, arialFont);
	whitePlayer->OnRender(spriteBatch, arialFont);

	spriteBatch.End();
	renderer.PresentScreen();
}

Board* Game::GetBoard()
{
	return &board;
}