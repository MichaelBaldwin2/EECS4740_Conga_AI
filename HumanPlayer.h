#pragma once

#include "Agent.h"
#include "Vector2Int.h"

class HumanPlayer : public Agent
{
private:
	Vector2Int selectedCell;

public:
	HumanPlayer();
	Move GetMove(Board board, SDL_MouseButtonEvent& mb);
	void OnRender(SpriteBatch& spriteBatch, SpriteFont font) {}
};
