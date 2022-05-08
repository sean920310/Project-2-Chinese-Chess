#include "Chess.h"

Chess::Chess(const Team& team)
{
	this->team = team;
}

void Chess::setPosition(Coord coord)
{
	float x, y;
	x = CHECKBOARD_SCALE_SIZE * (coord.x * 233.75 + 34)+ 35.0625 - CHESS_SCALE_SIZE * (606.0 / 2);
	y = CHECKBOARD_SCALE_SIZE * (coord.y * 233.75 + 34) + 58.05 - CHESS_SCALE_SIZE * (606.0 / 2);
	chess.setPosition(sf::Vector2f(x, y));
}

void Chess::showSelect(sf::Vector2i mouseCoord)
{
	sf::IntRect chessRect = this->chess.getTextureRect();
	chessRect.left += this->chess.getPosition().x;
	chessRect.top += this->chess.getPosition().y;
	chessRect.height *= CHESS_SCALE_SIZE;
	chessRect.width *= CHESS_SCALE_SIZE;

	if (chessRect.contains(mouseCoord)) {
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

void General::move(Board& board, Coord fromCoord, Coord toCoord)
{
	
	return;
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

void Advisor::move(Board& board, Coord fromCoord, Coord toCoord)
{
	return;
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

void Elephant::move(Board& board, Coord fromCoord, Coord toCoord)
{
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

void Horse::move(Board& board, Coord fromCoord, Coord toCoord)
{
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

void Chariot::move(Board& board, Coord fromCoord, Coord toCoord)
{
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

void Cannon::move(Board& board, Coord fromCoord, Coord toCoord)
{
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

void Soldier::move(Board& board, Coord fromCoord, Coord toCoord)
{
}

