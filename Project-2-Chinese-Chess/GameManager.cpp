#include "GameManager.h"

//function
bool isChoiceToMove(sf::Vector2i mouseCoord, Coord coord) {

	float x, y;
	x = CHECKBOARD_SCALE_SIZE * (coord.x * 233.75 + 34) + 35.0625 - CHESS_SCALE_SIZE * (606.0 / 2);
	y = CHECKBOARD_SCALE_SIZE * (coord.y * 233.75 + 34) + 58.05 - CHESS_SCALE_SIZE * (606.0 / 2);
	sf::IntRect circle(x,y,60,60);
	return circle.contains(mouseCoord);
}




//class
GameManager::GameManager():board(),viewer()
{
	onBoard = board.getAllChess();
	currentPlayer = Team::Red;
}

void GameManager::inGame()
{
	InGameState state = InGameState::start;
	std::vector<Coord> canMovePosCoord;
	Coord coordChoiseChess,coordChoiseToMove;
	while (viewer.windowIsOpen())
	{
		onBoard = board.getAllChess();

		switch (state)
		{
		//======================================================start====================================================	**start a new game
		case InGameState::start: 
			this->board.newBoard();
			state = InGameState::selectChess;
			break;

		//====================================================selectChess================================================	**wait for press a object
		case InGameState::selectChess:
			for (auto& chess : onBoard) {
				chess->showSelect(viewer.getMousePosition(),currentPlayer);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&chess->isChoice()&&currentPlayer==chess->getTeam()) {
					state = InGameState::pressChess;
					break;
				}
			}
			for (auto& coord : canMovePosCoord) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isChoiceToMove(viewer.getMousePosition(), coord)) {
					coordChoiseToMove = coord;
					state = InGameState::choiceMove;
					break;
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && state != InGameState::pressChess) {
				canMovePosCoord.clear();
			}
			break;

		//====================================================pressChess================================================	**show the coord can move to
		case InGameState::pressChess:
			for (auto& chess : onBoard) {
				if (chess->isChoice()) {
					coordChoiseChess = chess->getCoord();
					std::cout << chess->getCoord().x << " " << chess->getCoord().y << " is press.\n";
					canMovePosCoord.clear();
					canMovePosCoord = chess->coordCanMove(board);
					state = InGameState::selectChess;
					break;
				}
			}
			break;

		//====================================================choiceMove================================================	**move the chess
		case InGameState::choiceMove:
			//board.getChess(coordChoiseChess)->move(board,coordChoiseToMove);
			board.moveChess(coordChoiseChess, coordChoiseToMove);
			state = InGameState::isCheck;
			break;

		//====================================================isCheck===================================================	**judge if one side is check or win
		case InGameState::isCheck:

			state = InGameState::selectChess;

			if (currentPlayer == Team::Red)
				currentPlayer = Team::Black;
			else
				currentPlayer = Team::Red;
			break;

		//==================================================oneSideWin==================================================	**decide to play anthor game
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
