#pragma once
#include <vector>

#include "GameHeader.h"
#include "Chess.h"

class Viewer
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Font font;
public:
	Viewer();
	~Viewer();
	
	bool windowIsOpen();
	void pollevent();
	sf::Vector2i getMousePosition();
	void close();
	void update();
	void clear();
	int showMenu();	//0:exit game 1:start new game 2:select a file
	void showCheck(Team team);
	void showWinner(Team team);
	int showOneMoreGame(); //choice -1:no select 0:no 1:yes
	void drawRightSideObject(Team team);
	void drawCanMovePos(std::vector<Coord> coords);
	void drawSprite(std::vector<sf::Sprite> sprites);
	void display();
};