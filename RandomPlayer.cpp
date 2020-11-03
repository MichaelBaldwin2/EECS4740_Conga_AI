#include "RandomPlayer.h"
#include <string>

Move RandomPlayer::GetMove()
{
    Move move = Move();
    move.x = std::rand() % 4;
    move.y = std::rand() % 4;
    move.direction = std::rand() % 8;
    return move;
}
