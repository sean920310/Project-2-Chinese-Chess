#include "Chess.h"

Chess::Chess(const Team& team) :coord({ 0,0 }), charater(Characters::General)
{
	this->team = team;
}

Chess::Chess(const Chess& rhs)
{
	this->team = rhs.team;
	this->chessTexture = rhs.chessTexture;
	this->chess = rhs.chess;
	this->coord = rhs.coord;
	this->charater = rhs.charater;
}

void Chess::setPosition(Coord coord)
{
	this->coord = coord;
	float x, y;
	x = CHECKBOARD_SCALE_SIZE * (coord.x * 233.75 + 34) + 35.0625 - CHESS_SCALE_SIZE * (606.0 / 2);
	y = CHECKBOARD_SCALE_SIZE * (coord.y * 233.75 + 34) + 58.05 - CHESS_SCALE_SIZE * (606.0 / 2);
	chess.setPosition(sf::Vector2f(x, y));
}

void Chess::showSelect(sf::Vector2i mouseCoord, Team team)
{
	sf::IntRect chessRect = this->chess.getTextureRect();
	chessRect.left = this->chess.getPosition().x;
	chessRect.top = this->chess.getPosition().y;
	chessRect.height *= CHESS_SCALE_SIZE;
	chessRect.width *= CHESS_SCALE_SIZE;

	if (chessRect.contains(mouseCoord) && this->team == team) {
		chess.setScale(sf::Vector2f(CHESS_CHOISE_SCALE_SIZE, CHESS_CHOISE_SCALE_SIZE));
		isSelect = true;
	}
	else
	{
		isSelect = false;
		chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
	}
}

sf::Sprite Chess::getSprite()
{
	return this->chess;
}

Coord Chess::getCoord()
{
	return coord;
}

Team Chess::getTeam()
{
	return team;
}

Characters Chess::getCharacter()
{
	return this->charater;
}

bool Chess::isChoice()
{
	return isSelect;
}

void Chess::removeWillCheckCoord(const Board& board, std::vector<Coord>& allCoord)
{
	std::vector<Coord> resultCoord;
	Coord originCoord = this->coord;
	for (const auto& toCoord : allCoord) {
		Board tempBoard = board;
		Team chessTeam;
		if (this->team == Team::Red)
			chessTeam = Team::Black;
		else
			chessTeam = Team::Red;

		tempBoard.moveChess(this->coord, toCoord);
		if (tempBoard.oneSideIsCheck(chessTeam)) {
			if (chessTeam != this->team) {
				continue;
			}
		}
		resultCoord.push_back(toCoord);
	}
	allCoord = resultCoord;
}

//==================================================General==================================================

General::General(const Team& team) :Chess(team)
{
	this->charater = Characters::General;
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_GENERAL_BLACK);
	else
		chessTexture.loadFromFile(CHESS_GENERAL_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

General::General(const Chess& rhs):Chess(rhs)
{
	
}

std::vector<Coord> General::coordCanMove(const Board& board)
{
	std::vector<Coord> canMove;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (this->moveable(board, { 4 + i,1 + j }))
				canMove.push_back({ 4 + i,1 + j });
		}
	}
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (this->moveable(board, { 4 + i,8 + j }))
				canMove.push_back({ 4 + i,8 + j });
		}
	}

	return canMove;
}

bool General::moveable(const Board& board, Coord toCoord)
{

	if (!((toCoord.x >= 3 && toCoord.x <= 5 && toCoord.y <= 2 && toCoord.y >= 0) || (toCoord.x >= 3 && toCoord.x <= 5 && toCoord.y <= 9 && toCoord.y >= 7)))
		return false;
	else if (toCoord == coord)
		return false;
	else
	{
		//General to General
		if (team == Team::Red && (toCoord.x >= 3 && toCoord.x <= 5 && toCoord.y <= 2 && toCoord.y >= 0) && board.getChess(toCoord) != nullptr) {
			for (int i = toCoord.y + 1; i < this->coord.y; i++) {
				if (board.getChess({ this->coord.x,i }) != nullptr)
					return false;
			}
			if (board.getChess(toCoord)->getCharacter() == Characters::General && this->coord.x == toCoord.x)
				return true;
			else
				return false;
		}
		if (team == Team::Black && (toCoord.x >= 3 && toCoord.x <= 5 && toCoord.y <= 9 && toCoord.y >= 7) && board.getChess(toCoord) != nullptr) {
			for (int i = this->coord.y + 1; i < toCoord.y; i++) {
				if (board.getChess({ this->coord.x,i }) != nullptr)
					return false;
			}
			if (board.getChess(toCoord)->getCharacter() == Characters::General && this->coord.x == toCoord.x)
				return true;
			else
				return false;
		}

		//else
		if (abs(toCoord.x - this->coord.x) > 1 || abs(toCoord.y - this->coord.y) > 1)
			return false;
		if (abs(toCoord.x - this->coord.x) && abs(toCoord.y - this->coord.y))
			return false;
		if (board.getChess(toCoord) != nullptr) {
			if (board.getChess(toCoord)->getTeam() != this->team)
				return true;
			else
				return false;
		}
		else
		{
			return true;
		}
	}
}

//==================================================Advisor==================================================

Advisor::Advisor(const Team& team) :Chess(team)
{
	this->charater = Characters::Advisor;
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_ADVISOR_BLACK);
	else
		chessTexture.loadFromFile(CHESS_ADVISOR_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

Advisor::Advisor(const Chess& rhs):Chess(rhs)
{
}

std::vector<Coord> Advisor::coordCanMove(const Board& board)
{

	std::vector<Coord> canMove;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (this->moveable(board, { this->coord.x + i,this->coord.y + j }))
				canMove.push_back({ this->coord.x + i,this->coord.y + j });
		}
	}

	return canMove;
}

bool Advisor::moveable(const Board& board, Coord toCoord)
{
	if (this->team == Team::Red && (toCoord.x < 3 || toCoord.x>5 || toCoord.y > 9 || toCoord.y < 7))
		return false;
	else if (this->team == Team::Black && (toCoord.x < 3 || toCoord.x>5 || toCoord.y > 2 || toCoord.y < 0))
		return false;
	else if (toCoord == coord)
		return false;
	else if ((1 != abs(toCoord.x - this->coord.x)) || (1 != abs(toCoord.y - this->coord.y))) {
		return false;
	}
	else {
		if (board.getChess(toCoord) != nullptr) {
			if (board.getChess(toCoord)->getTeam() != this->team)
				return true;
			else
				return false;
		}
		else
		{
			return true;
		}
	}
}


//==================================================Elephant==================================================

Elephant::Elephant(const Team& team) :Chess(team)
{
	this->charater = Characters::Elephant;
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_ELEPHANT_BLACK);
	else
		chessTexture.loadFromFile(CHESS_ELEPHANT_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

Elephant::Elephant(const Chess& rhs):Chess(rhs)
{
}

std::vector<Coord> Elephant::coordCanMove(const Board& board)
{
	std::vector<Coord> canMove;
	for (int i = -2; i <= 2; i += 4) {
		for (int j = -2; j <= 2; j += 4) {
			if (this->moveable(board, { this->coord.x + i,this->coord.y + j }))
				canMove.push_back({ this->coord.x + i,this->coord.y + j });
		}
	}
	return canMove;
}

bool Elephant::moveable(const Board& board, Coord toCoord)
{
	Coord tempCoord = toCoord;
	tempCoord.x -= (toCoord.x - this->coord.x) / 2;
	tempCoord.y -= (toCoord.y - this->coord.y) / 2;


	if (toCoord == coord) {
		return false;
	}
	else if (toCoord.x < 0 || toCoord.x>8 || toCoord.y < 0 || toCoord.y>9) {
		return false;
	}
	else if ((2 != abs(toCoord.x - this->coord.x)) || (2 != abs(toCoord.y - this->coord.y))) {
		return false;
	}
	else if (board.getChess(tempCoord) != nullptr)
	{
		return false;
	}
	else if (this->team == Team::Black && toCoord.y > 4)
	{
		return false;
	}
	else if (this->team != Team::Black && toCoord.y < 5)
	{
		return false;
	}
	else {
		if (board.getChess(toCoord) != nullptr) {
			if (board.getChess(toCoord)->getTeam() != this->team)
				return true;
			else
				return false;
		}
		else
		{
			return true;
		}
	}
}


//==================================================Horse==================================================

Horse::Horse(const Team& team) :Chess(team)
{
	this->charater = Characters::Horse;
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_HORSE_BLACK);
	else
		chessTexture.loadFromFile(CHESS_HORSE_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

Horse::Horse(const Chess& rhs):Chess(rhs)
{
}

std::vector<Coord> Horse::coordCanMove(const Board& board)
{
	std::vector<Coord> canMove;
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			if (this->moveable(board, { this->coord.x + i,this->coord.y + j }))
				canMove.push_back({ this->coord.x + i,this->coord.y + j });
		}
	}
	return canMove;
}

bool Horse::moveable(const Board& board, Coord toCoord)
{
	Coord tempCoord = this->coord;
	int xdif = toCoord.x - this->coord.x;
	int ydif = toCoord.y - this->coord.y;
	int dif = abs(xdif) - abs(ydif);
	if (abs(xdif) > abs(ydif)) {
		tempCoord.x += xdif / 2;
	}
	else
	{
		tempCoord.y += ydif / 2;
	}


	if (toCoord == coord) {
		return false;
	}
	else if (toCoord.x < 0 || toCoord.x>8 || toCoord.y < 0 || toCoord.y>9) {
		return false;
	}

	else if (abs(dif) != 1 || dif == 0 || ydif == 0 || xdif == 0) {
		return false;
	}
	else if (board.getChess(tempCoord) != nullptr)
	{
		return false;
	}
	else {
		if (board.getChess(toCoord) != nullptr) {
			if (board.getChess(toCoord)->getTeam() != this->team)
				return true;
			else
				return false;
		}
		else
		{
			return true;
		}
	}
}


//==================================================Chariot==================================================

Chariot::Chariot(const Team& team) :Chess(team)
{
	this->charater = Characters::Chariot;
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_CHARIOT_BLACK);
	else
		chessTexture.loadFromFile(CHESS_CHARIOT_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

Chariot::Chariot(const Chess& rhs):Chess(rhs)
{
}

std::vector<Coord> Chariot::coordCanMove(const Board& board)
{
	std::vector<Coord> canMove;
	for (int i = 0; i < 9; i++) {
		if (this->moveable(board, { i,this->coord.y }))
			canMove.push_back({ i,this->coord.y });
	}
	for (int i = 0; i < 10; i++) {
		if (this->moveable(board, { this->coord.x,i }))
			canMove.push_back({ this->coord.x,i });
	}
	return canMove;
}

bool Chariot::moveable(const Board& board, Coord toCoord)
{
	if (toCoord.x < 0 || toCoord.x>8 || toCoord.y > 9 || toCoord.y < 0)
		return false;
	else if (toCoord == coord)
		return false;
	else
	{
		if ((toCoord.x - this->coord.x) && (toCoord.y - this->coord.y))	//�צV����
			return false;
		else
		{
			if (toCoord.x - this->coord.x) {	//���k����
				int start, end;
				if ((toCoord.x - this->coord.x) > 0) {
					start = this->coord.x + 1;
					end = toCoord.x;
				}
				else
				{
					start = toCoord.x + 1;
					end = this->coord.x;
				}
				for (int i = start; i < end; i++) {
					if (board.getChess({ i,toCoord.y }) != nullptr) {
						return false;
					}
				}
			}
			else													//�W�U����
			{
				int start, end;
				if ((toCoord.y - this->coord.y) > 0) {
					start = this->coord.y + 1;
					end = toCoord.y;
				}
				else
				{
					start = toCoord.y + 1;
					end = this->coord.y;
				}
				for (int i = start; i < end; i++) {
					if (board.getChess({ toCoord.x,i }) != nullptr) {
						return false;
					}
				}
			}
			if (board.getChess(toCoord) != nullptr) {
				return this->team != board.getChess(toCoord)->getTeam();
			}
			else
			{
				return true;
			}
		}
	}
}

//==================================================Cannon==================================================

Cannon::Cannon(const Team& team) :Chess(team)
{
	this->charater = Characters::Cannon;
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_CANNON_BLACK);
	else
		chessTexture.loadFromFile(CHESS_CANNON_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

Cannon::Cannon(const Chess& rhs):Chess(rhs)
{
}

std::vector<Coord> Cannon::coordCanMove(const Board& board)
{
	std::vector<Coord> canMove;
	for (int i = 0; i < 9; i++) {
		if (this->moveable(board, { i,this->coord.y }))
			canMove.push_back({ i,this->coord.y });
	}
	for (int i = 0; i < 10; i++) {
		if (this->moveable(board, { this->coord.x,i }))
			canMove.push_back({ this->coord.x,i });
	}
	return canMove;
}

bool Cannon::moveable(const Board& board, Coord toCoord)
{
	if (toCoord.x < 0 || toCoord.x>8 || toCoord.y > 9 || toCoord.y < 0)
		return false;
	else if (toCoord == coord)
		return false;
	else
	{
		if ((toCoord.x - this->coord.x) && (toCoord.y - this->coord.y))	//�צV����
			return false;
		else
		{
			bool cross = false;
			if (toCoord.x - this->coord.x) {	//���k����
				int start, end;
				if ((toCoord.x - this->coord.x) > 0) {
					start = this->coord.x + 1;
					end = toCoord.x;
				}
				else
				{
					start = toCoord.x + 1;
					end = this->coord.x;
				}
				for (int i = start; i < end; i++) {
					if (board.getChess({ i,toCoord.y }) != nullptr) {
						if (cross)
							return false;
						else
							cross = true;
					}
				}
			}
			else													//�W�U����
			{
				int start, end;
				if ((toCoord.y - this->coord.y) > 0) {
					start = this->coord.y + 1;
					end = toCoord.y;
				}
				else
				{
					start = toCoord.y + 1;
					end = this->coord.y;
				}
				for (int i = start; i < end; i++) {
					if (board.getChess({ toCoord.x,i }) != nullptr) {
						if (cross)
							return false;
						else
							cross = true;
					}
				}
			}
			if (board.getChess(toCoord) != nullptr) {
				if (cross)
					return this->team != board.getChess(toCoord)->getTeam();
				else
					return false;
			}
			else
			{
				return !cross;
			}
		}
	}
}

//==================================================Soldier==================================================

Soldier::Soldier(const Team& team) :Chess(team)
{
	this->charater = Characters::Soldier;
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_SOLDIER_BLACK);
	else
		chessTexture.loadFromFile(CHESS_SOLDIER_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

Soldier::Soldier(const Chess& rhs):Chess(rhs)
{
}

std::vector<Coord> Soldier::coordCanMove(const Board& board)
{
	std::vector<Coord> canMove;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (this->moveable(board, { this->coord.x + i,this->coord.y + j }))
				canMove.push_back({ this->coord.x + i,this->coord.y + j });
		}
	}
	return canMove;
}

bool Soldier::moveable(const Board& board, Coord toCoord)
{
	if (toCoord == coord)
		return false;
	if (this->team == Team::Red) {
		if (this->coord.y < 5)
			this->isCrossRiver = true;
	}
	else
	{
		if (this->coord.y > 4)
			this->isCrossRiver = true;
	}
	if (!(this->isCrossRiver) && abs(toCoord.x - this->coord.x))
		return false;
	if (this->team == Team::Red) {
		if (toCoord.x < 0 || toCoord.x>8 || toCoord.y > 6 || toCoord.y < 0)
			return false;
		else
		{
			if (abs(toCoord.x - this->coord.x) > 1 || abs(toCoord.y - this->coord.y) > 1 || (toCoord.y - this->coord.y) > 0)
				return false;
			if (abs(toCoord.x - this->coord.x) && abs(toCoord.y - this->coord.y))
				return false;
			if (board.getChess(toCoord) != nullptr) {
				if (board.getChess(toCoord)->getTeam() != this->team)
					return true;
				else
					return false;
			}
			else
			{
				return true;
			}
		}
	}
	else {
		if (toCoord.x < 0 || toCoord.x>8 || toCoord.y > 9 || toCoord.y < 3)
			return false;
		else
		{
			if (abs(toCoord.x - this->coord.x) > 1 || abs(toCoord.y - this->coord.y) > 1 || (toCoord.y - this->coord.y) < 0)
				return false;
			if (abs(toCoord.x - this->coord.x) && abs(toCoord.y - this->coord.y))
				return false;
			if (board.getChess(toCoord) != nullptr) {
				if (board.getChess(toCoord)->getTeam() != this->team)
					return true;
				else
					return false;
			}
			else
			{
				return true;
			}
		}
	}
}

