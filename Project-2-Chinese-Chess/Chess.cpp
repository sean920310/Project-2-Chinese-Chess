#include "Chess.h"

Chess::Chess(const Team& team) :coord({ 0,0 })
{
	this->team = team;
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

void General::move(Board& board, Coord toCoord)
{
	if (this->moveable(board, toCoord)) {
		board.moveChess(this->coord, toCoord);
	}
	else
	{
		std::cout << this->coord.x << " " << this->coord.y << " can't move to " << toCoord.x << " " << toCoord.y << std::endl;
	}
}

std::vector<Coord> General::coordCanMove(Board& board)
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

	//check if the move will be check


	return canMove;
}

bool General::moveable(Board& board, Coord toCoord)
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
			if (board.getChess(toCoord)->getCharacter() == Characters::General)
				return true;
			else
				return false;
		}
		if (team == Team::Black && (toCoord.x >= 3 && toCoord.x <= 5 && toCoord.y <= 9 && toCoord.y >= 7) && board.getChess(toCoord) != nullptr) {
			for (int i = this->coord.y + 1; i < toCoord.y; i++) {
				if (board.getChess({ this->coord.x,i }) != nullptr)
					return false;
			}
			if (board.getChess(toCoord)->getCharacter() == Characters::General)
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

void Advisor::move(Board& board, Coord toCoord)
{
	if (this->moveable(board, toCoord)) {
		board.moveChess(this->coord, toCoord);
	}
	else
	{
		std::cout << this->coord.x << " " << this->coord.y << " can't move to " << toCoord.x << " " << toCoord.y << std::endl;
	}
}

std::vector<Coord> Advisor::coordCanMove(Board& board)
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

bool Advisor::moveable(Board& board, Coord toCoord)
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

void Elephant::move(Board& board, Coord toCoord)
{
	if (this->moveable(board, toCoord)) {
		board.moveChess(this->coord, toCoord);
	}
	else
	{
		std::cout << this->coord.x << " " << this->coord.y << " can't move to " << toCoord.x << " " << toCoord.y << std::endl;
	}
}

std::vector<Coord> Elephant::coordCanMove(Board& board)
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

bool Elephant::moveable(Board& board, Coord toCoord)
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

void Horse::move(Board& board, Coord toCoord)
{
	if (this->moveable(board, toCoord)) {
		board.moveChess(this->coord, toCoord);
	}
	else
	{
		std::cout << this->coord.x << " " << this->coord.y << " can't move to " << toCoord.x << " " << toCoord.y << std::endl;
	}
}

std::vector<Coord> Horse::coordCanMove(Board& board)
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

bool Horse::moveable(Board& board, Coord toCoord)
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

void Chariot::move(Board& board, Coord toCoord)
{
	if (this->moveable(board, toCoord)) {
		board.moveChess(this->coord, toCoord);
	}
	else
	{
		std::cout << this->coord.x << " " << this->coord.y << " can't move to " << toCoord.x << " " << toCoord.y << std::endl;
	}
}

std::vector<Coord> Chariot::coordCanMove(Board& board)
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

bool Chariot::moveable(Board& board, Coord toCoord)
{
	if (toCoord.x < 0 || toCoord.x>8 || toCoord.y > 9 || toCoord.y < 0)
		return false;
	else if (toCoord == coord)
		return false;
	else
	{
		if ((toCoord.x - this->coord.x) && (toCoord.y - this->coord.y))	//斜向移動
			return false;
		else
		{
			if (toCoord.x - this->coord.x) {	//左右移動
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
			else													//上下移動
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

void Cannon::move(Board& board, Coord toCoord)
{
	if (this->moveable(board, toCoord)) {
		board.moveChess(this->coord, toCoord);
	}
	else
	{
		std::cout << this->coord.x << " " << this->coord.y << " can't move to " << toCoord.x << " " << toCoord.y << std::endl;
	}
}

std::vector<Coord> Cannon::coordCanMove(Board& board)
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

bool Cannon::moveable(Board& board, Coord toCoord)
{
	if (toCoord.x < 0 || toCoord.x>8 || toCoord.y > 9 || toCoord.y < 0)
		return false;
	else if (toCoord == coord)
		return false;
	else
	{
		if ((toCoord.x - this->coord.x) && (toCoord.y - this->coord.y))	//斜向移動
			return false;
		else
		{
			bool cross = false;
			if (toCoord.x - this->coord.x) {	//左右移動
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
			else													//上下移動
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

void Soldier::move(Board& board, Coord toCoord)
{
	if (this->moveable(board, toCoord)) {
		board.moveChess(this->coord, toCoord);
		if (this->team == Team::Red) {
			if (toCoord.y < 5)
				this->isCrossRiver = true;
		}
		else
		{
			if (toCoord.y > 4)
				this->isCrossRiver = true;
		}
	}
	else
	{
		std::cout << this->coord.x << " " << this->coord.y << " can't move to " << toCoord.x << " " << toCoord.y << std::endl;
	}
}

std::vector<Coord> Soldier::coordCanMove(Board& board)
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

bool Soldier::moveable(Board& board, Coord toCoord)
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

