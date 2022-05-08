#include "GameManager.h"

GameManager::GameManager():board(),viewer()
{
	onBoard = board.getChess();
	currentPlayer = Team::Red;
}

void GameManager::inGame()
{
	while (viewer.windowIsOpen())
	{
		onBoard = board.getChess();
		viewer.update(onBoard);

		//draw
		auto boardSprites = this->board.getAllSprite();
		viewer.render(boardSprites);
	}
}
