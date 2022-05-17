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
	bool clickLock = false;
public:
	Viewer();
	~Viewer();
	
	bool windowIsOpen();
	int pollevent();
	sf::Vector2i getMousePosition();
	bool mouseClick(sf::Mouse::Button button);
	void close();
	//0:not event 1:close 2:pause 
	int update();
	void clear();
	//0:exit game 1:start new game 2:select a file
	int showMenu();	
	void showCheck(Team team);
	void showWinner(Team team);
	//-1:no select 0:no 1:yes
	int showOneMoreGame();
	//-1:no select 0:continue 1:to menu
	int showPause();
	void drawRightSideObject(Team team);
	void drawCanMovePos(std::vector<Coord> coords);
	void drawSprite(std::vector<sf::Sprite> sprites);
	void display();
};