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
public:
	Viewer();
	~Viewer();
	
	bool windowIsOpen();
	void pollevent();
	sf::Vector2i getMousePosition();
	void update();
	void clear();
	void drawCanMovePos(std::vector<Coord> coords);
	void drawSprite(std::vector<sf::Sprite> sprites);
	void display();
};

