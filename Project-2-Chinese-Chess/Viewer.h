#pragma once
#include "GameHeader.h"
#include "Chess.h"
#include "Board.h"

class Viewer
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	Board board;
	King blackKing;
public:
	Viewer();
	~Viewer();
	
	bool windowIsOpen();
	void pollevent();
	void update();
	void render();
};

