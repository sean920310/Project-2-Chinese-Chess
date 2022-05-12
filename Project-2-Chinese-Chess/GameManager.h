#pragma once
#include<vector>
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

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
	std::fstream file;
	std::wstring filePath;

public:	
	GameManager();
	~GameManager();
	int menu();
	void readFile();
	void inGame(InGameState state);
	bool endGame(Team team);
	void logFile(Coord from, Coord to);
};



