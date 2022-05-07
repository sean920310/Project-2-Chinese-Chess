#pragma once
#include "GameHeader.h"

class Chess
{
protected:
	Team team;
	sf::Texture chessTexture;
	sf::Sprite chess;
public:
	Chess(const Team& team);
	virtual void move()=0;
	sf::Sprite getSprite();
};

class King :public Chess
{
public:
	King(const Team& team);
	virtual void move() override;
	sf::Sprite getSprite();
};



