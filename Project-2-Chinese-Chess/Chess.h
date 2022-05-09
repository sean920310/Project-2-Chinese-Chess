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
	bool isSelect = false;
public:
	//constructor
	Chess(const Team& team = Team::Black);

	//function
	void setPosition(Coord coord);
	void showSelect(sf::Vector2i mouseCoord,Team team);
	sf::Sprite getSprite();
	Coord getCoord();
	Team getTeam();
	bool isChoice();

	//move function
	virtual void move(Board& board, Coord toCoord) = 0;
	virtual std::vector<Coord> coordCanMove(Board& board) = 0;
	virtual bool moveable(Board& board, Coord toCoord) = 0;
};

class General :public Chess
{
public:
	General(const Team& team = Team::Black);
	virtual void move(Board& board, Coord toCoord) override;
	virtual std::vector<Coord> coordCanMove(Board& board) override;
	virtual bool moveable(Board& board, Coord toCoord) override;
};

class Advisor :public Chess
{
public:
	Advisor(const Team& team = Team::Black);
	virtual void move(Board& board, Coord toCoord) override;
	virtual std::vector<Coord> coordCanMove(Board& board) override;
	virtual bool moveable(Board& board, Coord toCoord) override;
};

class Elephant :public Chess
{
public:
	Elephant(const Team& team = Team::Black);
	virtual void move(Board& board, Coord toCoord) override;
	virtual std::vector<Coord> coordCanMove(Board& board) override;
	virtual bool moveable(Board& board, Coord toCoord) override;
};


class Horse :public Chess
{
public:
	Horse(const Team& team = Team::Black);
	virtual void move(Board& board, Coord toCoord) override;
	virtual std::vector<Coord> coordCanMove(Board& board) override;
	virtual bool moveable(Board& board, Coord toCoord) override;
};

class Chariot :public Chess
{
public:
	Chariot(const Team& team = Team::Black);
	virtual void move(Board& board, Coord toCoord) override;
	virtual std::vector<Coord> coordCanMove(Board& board) override;
	virtual bool moveable(Board& board, Coord toCoord) override;
};

class Cannon :public Chess
{
public:
	Cannon(const Team& team = Team::Black);
	virtual void move(Board& board, Coord toCoord) override;
	virtual std::vector<Coord> coordCanMove(Board& board) override;
	virtual bool moveable(Board& board, Coord toCoord) override;
};

class Soldier :public Chess
{
protected:
	bool isCrossRiver = false;
public:
	Soldier(const Team& team = Team::Black);
	virtual void move(Board& board, Coord toCoord) override;
	virtual std::vector<Coord> coordCanMove(Board& board) override;
	virtual bool moveable(Board& board, Coord toCoord) override;
};
