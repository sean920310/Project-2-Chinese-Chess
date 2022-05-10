#include "GameManager.h"

//function
bool isChoiceToMove(sf::Vector2i mouseCoord, Coord coord) {

	float x, y;
	x = CHECKBOARD_SCALE_SIZE * (coord.x * 233.75 + 34) + 35.0625 - CHESS_SCALE_SIZE * (606.0 / 2);
	y = CHECKBOARD_SCALE_SIZE * (coord.y * 233.75 + 34) + 58.05 - CHESS_SCALE_SIZE * (606.0 / 2);
	sf::IntRect circle(x,y,60,60);
	return circle.contains(mouseCoord);
}

bool oneSideIsCheck(Board& board,Team& team) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			if (board.getChess({ i,j }) != nullptr) {
				auto canMovePosCoord =  board.getChess({ i,j })->coordCanMove(board);
				for (const auto& coord : canMovePosCoord) {
					if (board.getChess(coord) != nullptr) {
						if (board.getChess(coord)->getCharacter() == Characters::General) {
							team = board.getChess({ i,j })->getTeam();
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool oneSideIsWin(Board& board, Team& team) {
	bool redAlive = false;
	bool blackAlive = false;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			if (board.getChess({ i,j }) != nullptr) {
				if (board.getChess({ i,j })->getCharacter() == Characters::General) {
					if (board.getChess({ i,j })->getTeam() == Team::Red) {
						team = Team::Black;
						redAlive = true;
					}
					else
					{
						team = Team::Red;
						blackAlive = true;
					}
				}			
			}
		}
	}
	return !(redAlive && blackAlive);
}
//class
GameManager::GameManager():board(),viewer()
{
	onBoard = board.getAllChess();
	currentPlayer = Team::Red;
}

int GameManager::menu()
{
	return 0;
}


void GameManager::inGame()
{
	InGameState state = InGameState::start;
	std::vector<Coord> canMovePosCoord;
	Coord coordChoiseChess,coordChoiseToMove;
	bool isCheck=false,isWin=false;
	Team teamCheck=Team::Black,teamWin = Team::Black;

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
			state = InGameState::oneSideWin;
			break;

		//====================================================isCheck===================================================	**judge if one side is check or win
		case InGameState::isCheck:
			if (oneSideIsCheck(board, teamCheck)) {
				isCheck = true;
			}
			else
			{
				isCheck = false;
			}
			state = InGameState::selectChess;
			
			if (currentPlayer == Team::Red)
				currentPlayer = Team::Black;
			else
				currentPlayer = Team::Red;
			break;

		//==================================================oneSideWin==================================================	**decide to play anthor game
		case InGameState::oneSideWin:
			if (oneSideIsWin(board, teamWin)) {
				if (this->endGame(teamWin))
					state = InGameState::start;
				else
					return;
				
			}
			else
			{
				state = InGameState::isCheck;
			}
			break;
		}


		//draw
		viewer.update();
		viewer.clear();
		auto boardSprites = this->board.getAllSprite();
		viewer.drawSprite(boardSprites);
		viewer.drawCanMovePos(canMovePosCoord);
		viewer.drawRightSideObject(currentPlayer);
		if(isCheck)
			viewer.showCheck(teamCheck);
		viewer.display();
	}

}

bool GameManager::endGame(Team teamWin)
{
	while (viewer.windowIsOpen()) {
		viewer.update();
		viewer.clear();
		auto boardSprites = this->board.getAllSprite();
		viewer.drawSprite(boardSprites);
		viewer.showWinner(teamWin);
		viewer.display();
	}
	return false;
}