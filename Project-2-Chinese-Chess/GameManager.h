#pragma once
#include<vector>

#include"GameHeader.h"
#include "Board.h"
#include "Chess.h"
#include "Viewer.h"

class GameManager
{
private:
	std::vector<Chess*> on_board;
	int current_player;		//1:red , 2:black
	Board board;
	Viewer viewer;
	std::vector<sf::Sprite> sprites;
public:
	GameManager();
	void run();
};

