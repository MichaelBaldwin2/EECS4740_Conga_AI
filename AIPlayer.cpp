#include "AIPlayer.h"
#include "Minimax.h"
#include <iostream>

Move AIPlayer::GetMove(Board& board) {
	Move move = Move();
	Minimax minimax = Minimax();

	bool isWhite = (this->name).compare("White") == 0;
	minimax.GenerateTree(isWhite, board);
	std::cout << "Game Tree Size: " << minimax.gameTree.size() << std::endl;
	move = minimax.GetOptimalMove(0, 0, true).move;

	return move;
}