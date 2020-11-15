#pragma once

#include "Agent.h"

class RandomPlayer : public Agent
{

public:
	Move GetMove(Board board, SDL_MouseButtonEvent& mb);
	void OnRender(SpriteBatch& spriteBatch, SpriteFont font) {}
};
