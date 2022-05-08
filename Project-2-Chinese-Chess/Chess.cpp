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
	chessRect.left += this->chess.getPosition().x;
	chessRect.top += this->chess.getPosition().y;
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

bool Chess::isChoice()
{
	return isSelect;
}

//==================================================General==================================================

General::General(const Team& team) :Chess(team)
{
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
			if (this->moveable(board, { this->coord.x + i,this->coord.y + j }))
				canMove.push_back({ this->coord.x + i,this->coord.y + j });
		}
	}
	return canMove;
}

bool General::moveable(Board& board, Coord toCoord)
{
	if (toCoord.x < 3 || toCoord.x>5 || toCoord.y > 9 || toCoord.y < 7)
		return false;
	else if(toCoord == coord)
		return false;
	else
	{
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
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_ADVISOR_BLACK);
	else
		chessTexture.loadFromFile(CHESS_ADVISOR_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

void Advisor::move(Board& board, Coord toCoord)
{
	return;
}

std::vector<Coord> Advisor::coordCanMove(Board& board)
{
	return std::vector<Coord>();
}

bool Advisor::moveable(Board& board, Coord toCoord)
{
	return false;
}


//==================================================Elephant==================================================

Elephant::Elephant(const Team& team) :Chess(team)
{
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_ELEPHANT_BLACK);
	else
		chessTexture.loadFromFile(CHESS_ELEPHANT_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

void Elephant::move(Board& board, Coord toCoord)
{
}

std::vector<Coord> Elephant::coordCanMove(Board& board)
{
	return std::vector<Coord>();
}

bool Elephant::moveable(Board& board, Coord toCoord)
{
	return false;
}


//==================================================Horse==================================================

Horse::Horse(const Team& team) :Chess(team)
{
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_HORSE_BLACK);
	else
		chessTexture.loadFromFile(CHESS_HORSE_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

void Horse::move(Board& board, Coord toCoord)
{
}

std::vector<Coord> Horse::coordCanMove(Board& board)
{
	return std::vector<Coord>();
}

bool Horse::moveable(Board& board, Coord toCoord)
{
	return false;
}


//==================================================Chariot==================================================

Chariot::Chariot(const Team& team) :Chess(team)
{
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_CHARIOT_BLACK);
	else
		chessTexture.loadFromFile(CHESS_CHARIOT_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

void Chariot::move(Board& board, Coord toCoord)
{
}

std::vector<Coord> Chariot::coordCanMove(Board& board)
{
	return std::vector<Coord>();
}

bool Chariot::moveable(Board& board, Coord toCoord)
{
	return false;
}

//==================================================Cannon==================================================

Cannon::Cannon(const Team& team) :Chess(team)
{
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_CANNON_BLACK);
	else
		chessTexture.loadFromFile(CHESS_CANNON_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

void Cannon::move(Board& board, Coord toCoord)
{
}

std::vector<Coord> Cannon::coordCanMove(Board& board)
{
	return std::vector<Coord>();
}

bool Cannon::moveable(Board& board, Coord toCoord)
{
	return false;
}

//==================================================Soldier==================================================

Soldier::Soldier(const Team& team) :Chess(team)
{
	if (team == Team::Black)
		chessTexture.loadFromFile(CHESS_SOLDIER_BLACK);
	else
		chessTexture.loadFromFile(CHESS_SOLDIER_RED);
	chess.setTexture(chessTexture);
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

void Soldier::move(Board& board, Coord toCoord)
{
}

std::vector<Coord> Soldier::coordCanMove(Board& board)
{
	return std::vector<Coord>();
}

bool Soldier::moveable(Board& board, Coord toCoord)
{
	return false;
}

