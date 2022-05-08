#pragma once
#include<vector>
#include<iostream>

#include"GameHeader.h"
#include "Board.h"
#include "Chess.h"
#include "Viewer.h"

class GameManager
{
private:
	std::vector<Chess*> onBoard;
	Team currentPlayer;		//1:red , 2:black
	Board board;
	Viewer viewer;
	std::vector<sf::Sprite> sprites;
public:
	GameManager();
	int menu();
	void inGame();

};



