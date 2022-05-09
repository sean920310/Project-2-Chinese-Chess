#include "Board.h"

Board::Board() :boardArr(9, std::vector<Chess*>(10, nullptr))
{
	//initialize checkboard
	checkBoardTexture.loadFromFile(CHECKBOARD);
	checkBoard.setTexture(checkBoardTexture);
	checkBoard.setPosition(sf::Vector2f(35.0625f, 58.05f));
	checkBoard.setScale(sf::Vector2f(CHECKBOARD_SCALE_SIZE, CHECKBOARD_SCALE_SIZE));

	//initialize chess
	General* blackGeneral, * redGeneral;
	blackGeneral = new General(Team::Black);
	redGeneral = new General(Team::Red);
	blackGeneral->setPosition({ 4,0 });
	redGeneral->setPosition({ 4,9 });


	Advisor* blackAdvisor[2], * redAdvisor[2];
	for (int i = 0; i < 2; i++) {
		blackAdvisor[i] = new Advisor(Team::Black);
		redAdvisor[i] = new Advisor(Team::Red);
	}
	blackAdvisor[0]->setPosition({ 3,0 });
	blackAdvisor[1]->setPosition({ 5,0 });
	redAdvisor[0]->setPosition({ 3,9 });
	redAdvisor[1]->setPosition({ 5,9 });

	Elephant* blackElephant[2], * redElephant[2];
	for (int i = 0; i < 2; i++) {
		blackElephant[i] = new Elephant(Team::Black);
		redElephant[i] = new Elephant(Team::Red);
	}
	blackElephant[0]->setPosition({ 2,0 });
	blackElephant[1]->setPosition({ 6,0 });
	redElephant[0]->setPosition({ 2,9 });
	redElephant[1]->setPosition({ 6,9 });

	Horse* blackHorse[2], * redHorse[2];
	for (int i = 0; i < 2; i++) {
		blackHorse[i] = new Horse(Team::Black);
		redHorse[i] = new Horse(Team::Red);
	}
	blackHorse[0]->setPosition({ 1,0 });
	blackHorse[1]->setPosition({ 7,0 });
	redHorse[0]->setPosition({ 1,9 });
	redHorse[1]->setPosition({ 7,9 });

	Chariot* blackChariot[2], * redChariot[2];
	for (int i = 0; i < 2; i++) {
		blackChariot[i] = new Chariot(Team::Black);
		redChariot[i] = new Chariot(Team::Red);
	}
	blackChariot[0]->setPosition({ 0,0 });
	blackChariot[1]->setPosition({ 8,0 });
	redChariot[0]->setPosition({ 0,9 });
	redChariot[1]->setPosition({ 8,9 });

	Cannon* blackCannon[2], * redCannon[2];
	for (int i = 0; i < 2; i++) {
		blackCannon[i] = new Cannon(Team::Black);
		redCannon[i] = new Cannon(Team::Red);
	}
	blackCannon[0]->setPosition({ 1,2 });
	blackCannon[1]->setPosition({ 7,2 });
	redCannon[0]->setPosition({ 1,7 });
	redCannon[1]->setPosition({ 7,7 });

	Soldier* blackSoldier[5], * redSoldier[5];
	for (int i = 0; i < 5; i++) {
		blackSoldier[i] = new Soldier(Team::Black);
		blackSoldier[i]->setPosition({ i * 2,3 });
		boardArr[i * 2][3] = blackSoldier[i];
		redSoldier[i] = new Soldier(Team::Red);
		redSoldier[i]->setPosition({ i * 2,6 });
		boardArr[i * 2][6] = redSoldier[i];

	}

	//initialize boardArr
	boardArr[4][0] = blackGeneral;
	boardArr[4][9] = redGeneral;
	boardArr[3][0] = blackAdvisor[0];
	boardArr[5][0] = blackAdvisor[1];
	boardArr[3][9] = redAdvisor[0];
	boardArr[5][9] = redAdvisor[1];
	boardArr[2][0] = blackElephant[0];
	boardArr[6][0] = blackElephant[1];
	boardArr[2][9] = redElephant[0];
	boardArr[6][9] = redElephant[1];
	boardArr[1][0] = blackHorse[0];
	boardArr[7][0] = blackHorse[1];
	boardArr[1][9] = redHorse[0];
	boardArr[7][9] = redHorse[1];
	boardArr[0][0] = blackChariot[0];
	boardArr[8][0] = blackChariot[1];
	boardArr[0][9] = redChariot[0];
	boardArr[8][9] = redChariot[1];
	boardArr[1][2] = blackCannon[0];
	boardArr[7][2] = blackCannon[1];
	boardArr[1][7] = redCannon[0];
	boardArr[7][7] = redCannon[1];
}

Board::Board(const Board & rhs)
{
	for (int i = 0; i < 9; i++) {
		this->boardArr[i] = rhs.boardArr[i];
	}
	this->checkBoardTexture = rhs.checkBoardTexture;
	this->checkBoard = rhs.checkBoard;
}

Board::~Board()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (boardArr[j][i] != nullptr)
				delete boardArr[j][i];
		}
	}
}

Board& Board::operator=(const Board& rhs)
{
	for (int i = 0; i < 9; i++) {
		this->boardArr[i] = rhs.boardArr[i];
	}
	this->checkBoardTexture = rhs.checkBoardTexture;
	this->checkBoard = rhs.checkBoard;
	return *this;
}

void Board::newBoard()
{
	//initialize checkboard
	checkBoardTexture.loadFromFile(CHECKBOARD);
	checkBoard.setTexture(checkBoardTexture);
	checkBoard.setPosition(sf::Vector2f(35.0625f, 58.05f));
	checkBoard.setScale(sf::Vector2f(CHECKBOARD_SCALE_SIZE, CHECKBOARD_SCALE_SIZE));

	//initialize chess
	General* blackGeneral, * redGeneral;
	blackGeneral = new General(Team::Black);
	redGeneral = new General(Team::Red);
	blackGeneral->setPosition({ 4,0 });
	redGeneral->setPosition({ 4,9 });


	Advisor* blackAdvisor[2], * redAdvisor[2];
	for (int i = 0; i < 2; i++) {
		blackAdvisor[i] = new Advisor(Team::Black);
		redAdvisor[i] = new Advisor(Team::Red);
	}
	blackAdvisor[0]->setPosition({ 3,0 }
	);
	blackAdvisor[1]->setPosition({ 5,0 });
	redAdvisor[0]->setPosition({ 3,9 });
	redAdvisor[1]->setPosition({ 5,9 });

	Elephant* blackElephant[2], * redElephant[2];
	for (int i = 0; i < 2; i++) {
		blackElephant[i] = new Elephant(Team::Black);
		redElephant[i] = new Elephant(Team::Red);
	}
	blackElephant[0]->setPosition({ 2,0 });
	blackElephant[1]->setPosition({ 6,0 });
	redElephant[0]->setPosition({ 2,9 });
	redElephant[1]->setPosition({ 6,9 });

	Horse* blackHorse[2], * redHorse[2];
	for (int i = 0; i < 2; i++) {
		blackHorse[i] = new Horse(Team::Black);
		redHorse[i] = new Horse(Team::Red);
	}
	blackHorse[0]->setPosition({ 1,0 });
	blackHorse[1]->setPosition({ 7,0 });
	redHorse[0]->setPosition({ 1,9 });
	redHorse[1]->setPosition({ 7,9 });

	Chariot* blackChariot[2], * redChariot[2];
	for (int i = 0; i < 2; i++) {
		blackChariot[i] = new Chariot(Team::Black);
		redChariot[i] = new Chariot(Team::Red);
	}
	blackChariot[0]->setPosition({ 0,0 });
	blackChariot[1]->setPosition({ 8,0 });
	redChariot[0]->setPosition({ 0,9 });
	redChariot[1]->setPosition({ 8,9 });

	Cannon* blackCannon[2], * redCannon[2];
	for (int i = 0; i < 2; i++) {
		blackCannon[i] = new Cannon(Team::Black);
		redCannon[i] = new Cannon(Team::Red);
	}
	blackCannon[0]->setPosition({ 1,2 });
	blackCannon[1]->setPosition({ 7,2 });
	redCannon[0]->setPosition({ 1,7 });
	redCannon[1]->setPosition({ 7,7 });

	Soldier* blackSoldier[5], * redSoldier[5];
	for (int i = 0; i < 5; i++) {
		blackSoldier[i] = new Soldier(Team::Black);
		blackSoldier[i]->setPosition({ i * 2,3 });
		boardArr[i * 2][3] = blackSoldier[i];
		redSoldier[i] = new Soldier(Team::Red);
		redSoldier[i]->setPosition({ i * 2,6 });
		boardArr[i * 2][6] = redSoldier[i];

	}

	//initialize boardArr
	boardArr[4][0] = blackGeneral;
	boardArr[4][9] = redGeneral;
	boardArr[3][0] = blackAdvisor[0];
	boardArr[5][0] = blackAdvisor[1];
	boardArr[3][9] = redAdvisor[0];
	boardArr[5][9] = redAdvisor[1];
	boardArr[2][0] = blackElephant[0];
	boardArr[6][0] = blackElephant[1];
	boardArr[2][9] = redElephant[0];
	boardArr[6][9] = redElephant[1];
	boardArr[1][0] = blackHorse[0];
	boardArr[7][0] = blackHorse[1];
	boardArr[1][9] = redHorse[0];
	boardArr[7][9] = redHorse[1];
	boardArr[0][0] = blackChariot[0];
	boardArr[8][0] = blackChariot[1];
	boardArr[0][9] = redChariot[0];
	boardArr[8][9] = redChariot[1];
	boardArr[1][2] = blackCannon[0];
	boardArr[7][2] = blackCannon[1];
	boardArr[1][7] = redCannon[0];
	boardArr[7][7] = redCannon[1];
}

Chess * Board::getChess(Coord coord)
{
	if (coord.x > 8 || coord.y > 9)
		return nullptr;
	else
		return boardArr[coord.x][coord.y];
}

std::vector<sf::Sprite> Board::getAllSprite()
{
	std::vector<sf::Sprite> allSprite;
	allSprite.push_back(checkBoard);
	for (const auto& row : boardArr) {
		for (const auto& chess : row) {
			if (chess != nullptr) {
				allSprite.push_back(chess->getSprite());
			}
		}
	}
	return allSprite;
}

std::vector<Chess*> Board::getAllChess()
{
	std::vector<Chess*> chessOnBoard;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (boardArr[j][i] != nullptr)
				chessOnBoard.push_back(boardArr[j][i]);
		}
	}
	return chessOnBoard;
}

void Board::moveChess(Coord fromCoord, Coord toCoord)
{
	this->boardArr[fromCoord.x][fromCoord.y]->setPosition(toCoord);

	auto temp = this->boardArr[fromCoord.x][fromCoord.y];
	if (this->getChess(toCoord) != nullptr)
		delete this->boardArr[toCoord.x][toCoord.y];

	this->boardArr[toCoord.x][toCoord.y] = temp;
	this->boardArr[fromCoord.x][fromCoord.y] = nullptr;
	
}



