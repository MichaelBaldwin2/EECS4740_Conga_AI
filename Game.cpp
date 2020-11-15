#include "Agent.h"
#include "AIPlayer.h"
#include "Board.h"
#include "Button.h"
#include "Game.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "RectInt.h"
#include "Renderer.h"
#include "Texture.h"
#include "Time.h"
#include "TTFFont.h"
#include "SpriteBatch.h"
#include "Window.h"
#include <SDL.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>

Agent* player;

Game::Game() : board(), isRunning(true), window(), renderer(), spriteBatch(), textures(), arialFontNormal(), pauseButton(), playButton(), stepButton(), resetButton(), blackPlayer(new RandomPlayer()), whitePlayer(new AIPlayer()), updateFPS(0), renderFPS(0), pauseSim(true), totalMoves(0), timeTaken(0), onLossText() {}

Game::~Game()
{
	delete whitePlayer;
	delete blackPlayer;

	// Clear all the textures
	for(auto it = textures.begin(); it != textures.end(); it++)
	{
		it->second.Free();
	}

	arialFontNormal.Free();
	arialFontHuge.Free();
	spriteBatch.Free();
	textures.clear();
	renderer.Free();
	window.Free();
}

bool Game::Init()
{
	window = Window(1280, 656, "Conga AI");
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
	textures["PauseButton"] = Texture(renderer, "gfx/PauseButton.png");
	textures["PlayButton"] = Texture(renderer, "gfx/PlayButton.png");
	textures["StepButton"] = Texture(renderer, "gfx/StepButton.png");
	textures["ResetButton"] = Texture(renderer, "gfx/ResetButton.png");

	pauseButton = Button(RectInt(656, 0, 64, 64), Sprite(textures["PauseButton"]), Color(128, 128, 128));
	playButton = Button(RectInt(720, 0, 64, 64), Sprite(textures["PlayButton"]), Color(128, 128, 128));
	stepButton = Button(RectInt(784, 0, 64, 64), Sprite(textures["StepButton"]), Color(128, 128, 128));
	resetButton = Button(RectInt(848, 0, 64, 64), Sprite(textures["ResetButton"]), Color(128, 128, 128));

	arialFontNormal = TTFFont("gfx/arial.ttf", 16);
	arialFontHuge = TTFFont("gfx/arial.ttf", 128);

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
				timeTaken = 0;
				onLossText = "";
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
			onLossText = player->name + " has lost!";
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

			// Change current player
			auto p = player == blackPlayer;
			switch(p)
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

			for(auto drawY = 0, i = 0; drawY < 64 && i < whiteStoneCount; drawY += 16)
			{
				for(auto drawX = 0; drawX < 64 && i < whiteStoneCount; drawX += 16, i++)
				{
					auto position = Vector2Int((75 + (x * 144)) + drawX, (75 + (y * 144)) + drawY);
					spriteBatch.Draw(Sprite(textures["WhiteStone"]), position, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.25f);
				}
			}
			for(int drawY = 0, i = 0; drawY < 64 && i < blackStoneCount; drawY += 16)
			{
				for(auto drawX = 0; drawX < 64 && i < blackStoneCount; drawX += 16, i++)
				{
					auto position = Vector2Int((75 + (x * 144)) + drawX, (75 + (y * 144)) + drawY);
					spriteBatch.Draw(Sprite(textures["BlackStone"]), position, Color::White, 0, Vector2::Zero, Vector2::One, SpriteFlip::None, 0.25f);
				}
			}
		}
	}

	//Render Pause, Play, Step, and Reset buttons
	pauseButton.OnRender(spriteBatch);
	playButton.OnRender(spriteBatch);
	stepButton.OnRender(spriteBatch);
	resetButton.OnRender(spriteBatch);

	// Render FPS and UPS
	spriteBatch.DrawString("FPS: " + std::to_string(renderFPS) + " (" + std::to_string(updateFPS) + ")", arialFontNormal, Vector2::Zero);

	// Render AI info
	spriteBatch.DrawString("Total Moves: " + std::to_string(totalMoves), arialFontNormal, Vector2(700, 72));
	spriteBatch.DrawString("Time Taken: " + std::to_string(timeTaken), arialFontNormal, Vector2(700, 88));
	spriteBatch.DrawString("Search Depth: " + std::to_string(static_cast<AIPlayer*>(whitePlayer)->GetTotalDepth()), arialFontNormal, Vector2(700, 104));
	spriteBatch.DrawString("Nodes Explored: " + std::to_string(static_cast<AIPlayer*>(whitePlayer)->GetExploredNodes()), arialFontNormal, Vector2(700, 120));
	spriteBatch.DrawString("Nodes Pruned: " + std::to_string(static_cast<AIPlayer*>(whitePlayer)->GetPrunedNodes()), arialFontNormal, Vector2(700, 136));

	// Render Win/Loss if game over
	if(!onLossText.empty())
	{
		spriteBatch.DrawString(onLossText, arialFontHuge, Vector2(64, 256));
	}

	spriteBatch.End();
	renderer.PresentScreen();
}