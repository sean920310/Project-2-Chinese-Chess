#include "GameManager.h"

GameManager::GameManager():board(),viewer()
{
	//board = Board::Board();
	current_player = 1;
}

void GameManager::run()
{
	//sprites.push_back(board.getSprite());
	while (viewer.windowIsOpen())
	{
		viewer.update();
		
		viewer.render();
	}
}
