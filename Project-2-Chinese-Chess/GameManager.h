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

	//0:exit game 1:start new game 2:select a file
	int menu();
	void inGame(InGameState state);
	bool endGame(Team team);
	//0:windows close 1:continue 2:to menu
	int pause();
	void readFile();
	void logFile(Coord from, Coord to);
};



