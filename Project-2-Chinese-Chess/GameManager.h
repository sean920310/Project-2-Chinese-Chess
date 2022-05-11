#pragma once
#include<vector>
#include<iostream>
#include <fstream>
#include <string>

#include"GameHeader.h"
#include "Board.h"
#include "Chess.h"
#include "Viewer.h"

bool isChoiceToMove(sf::Vector2i mouseCoord, Coord coord);

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
	void readFile();
	void inGame(InGameState state);
	bool endGame(Team team);

};



