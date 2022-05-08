#pragma once
#include "GameHeader.h"
class Board;
#include "Board.h"

class Chess
{
protected:
	Team team;
	sf::Texture chessTexture;
	sf::Sprite chess;
	bool isSelect=false;
public:
	Chess(const Team& team = Team::Black);
	void setPosition(Coord coord);
	void showSelect(sf::Vector2i mouseCoord);
	virtual void move(Board& board,Coord fromCoord,Coord toCoord)=0;
	sf::Sprite getSprite();
};

class General :public Chess
{
public:
	General(const Team& team = Team::Black);
	virtual void move(Board& board, Coord fromCoord, Coord toCoord) override;
};

class Advisor :public Chess
{
public:
	Advisor(const Team& team = Team::Black);
	virtual void move(Board& board, Coord fromCoord, Coord toCoord) override;
};

class Elephant :public Chess
{
public:
	Elephant(const Team& team = Team::Black);
	virtual void move(Board& board, Coord fromCoord, Coord toCoord) override;
};


class Horse :public Chess
{
public:
	Horse(const Team& team = Team::Black);
	virtual void move(Board& board, Coord fromCoord, Coord toCoord) override;
};

class Chariot :public Chess
{
public:
	Chariot(const Team& team = Team::Black);
	virtual void move(Board& board, Coord fromCoord, Coord toCoord) override;
};

class Cannon :public Chess
{
public:
	Cannon(const Team& team = Team::Black);
	virtual void move(Board& board, Coord fromCoord, Coord toCoord) override;
};

class Soldier :public Chess
{
public:
	Soldier(const Team& team = Team::Black);
	virtual void move(Board& board, Coord fromCoord, Coord toCoord) override;
};
