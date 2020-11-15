#pragma once

#include "Board.h"
#include "Move.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <SDL.h>
#include <string>

class Agent
{
public:
	std::string name;

public:
	virtual Move GetMove(Board board, SDL_MouseButtonEvent &mb) = 0;
	virtual void OnRender(SpriteBatch& spriteBatch, SpriteFont font) = 0;
};
