#pragma once
#include <iostream>
#include "GameHeader.h"
class Board;
#include "Board.h"

class Chess
{
protected:
	Team team;
	sf::Texture chessTexture;
	sf::Sprite chess;
	Coord coord;
	Characters charater;
	bool isSelect = false;
public:
	//constructor
	Chess(const Team& team = Team::Black);
	Chess(const Chess& rhs);

	//function
	void setPosition(Coord coord);
	void showSelect(sf::Vector2i mouseCoord, Team team);
	sf::Sprite getSprite();
	Coord getCoord();
	Team getTeam();
	Characters getCharacter();
	bool isChoice();
	//*check if the move will be check
	void removeWillCheckCoord(const Board& board, std::vector<Coord>& allCoord);

	//move function
	virtual std::vector<Coord> coordCanMove(const Board& board) = 0;
	virtual bool moveable(const Board& board, Coord toCoord) = 0;
};

class General :public Chess
{
public:
	General(const Team& team = Team::Black);
	General(const Chess& rhs);
	virtual std::vector<Coord> coordCanMove(const Board& board) override;
	virtual bool moveable(const Board& board, Coord toCoord) override;
};

class Advisor :public Chess
{
public:
	Advisor(const Team& team = Team::Black);
	Advisor(const Chess& rhs);
	virtual std::vector<Coord> coordCanMove(const Board& board) override;
	virtual bool moveable(const Board& board, Coord toCoord) override;
};

class Elephant :public Chess
{
public:
	Elephant(const Team& team = Team::Black);
	Elephant(const Chess& rhs);
	virtual std::vector<Coord> coordCanMove(const Board& board) override;
	virtual bool moveable(const Board& board, Coord toCoord) override;
};


class Horse :public Chess
{
public:
	Horse(const Team& team = Team::Black);
	Horse(const Chess& rhs);
	virtual std::vector<Coord> coordCanMove(const Board& board) override;
	virtual bool moveable(const Board& board, Coord toCoord) override;
};

class Chariot :public Chess
{
public:
	Chariot(const Team& team = Team::Black);
	Chariot(const Chess& rhs);
	virtual std::vector<Coord> coordCanMove(const Board& board) override;
	virtual bool moveable(const Board& board, Coord toCoord) override;
};

class Cannon :public Chess
{
public:
	Cannon(const Team& team = Team::Black);
	Cannon(const Chess& rhs);
	virtual std::vector<Coord> coordCanMove(const Board& board) override;
	virtual bool moveable(const Board& board, Coord toCoord) override;
};

class Soldier :public Chess
{
protected:
	bool isCrossRiver = false;
public:
	Soldier(const Team& team = Team::Black);
	Soldier(const Chess& rhs);
	virtual std::vector<Coord> coordCanMove(const Board& board) override;
	virtual bool moveable(const Board& board, Coord toCoord) override;
};
