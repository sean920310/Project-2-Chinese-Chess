#include "GameManager.h"

GameManager::GameManager():board(),viewer()
{
	onBoard = board.getAllChess();
	currentPlayer = Team::Red;
}

void GameManager::inGame()
{
	InGameState state = InGameState::start;
	std::vector<Coord> canMovePosCoord;
	while (viewer.windowIsOpen())
	{
		onBoard = board.getAllChess();

		switch (state)
		{
		case InGameState::start:
			this->board.newBoard();
			state = InGameState::selectChess;
			break;

		case InGameState::selectChess:
			for (auto& chess : onBoard) {
				chess->showSelect(viewer.getMousePosition(),currentPlayer);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&chess->isChoice()&&currentPlayer==chess->getTeam()) {
					state = InGameState::pressChess;
					break;
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && state != InGameState::pressChess) {
				canMovePosCoord.clear();
			}
			break;

		case InGameState::pressChess:
			for (auto& chess : onBoard) {
				if (chess->isChoice()) {
					std::cout << chess->getCoord().x << " " << chess->getCoord().y << " is press.\n";
					canMovePosCoord.clear();
					canMovePosCoord = chess->coordCanMove(board);
					state = InGameState::selectChess;
					break;
				}
			}
			break;

		case InGameState::choiceMove:

			break;

		case InGameState::isCheck:

			break;

		case InGameState::oneSideWin:
			
			break;
		}


		//draw
		viewer.update();
		viewer.clear();
		auto boardSprites = this->board.getAllSprite();
		viewer.drawSprite(boardSprites);
		viewer.drawCanMovePos(canMovePosCoord);
		viewer.display();
	}
}
