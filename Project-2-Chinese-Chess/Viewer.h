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
	void update(std::vector<Chess*> allChess);
	void render(std::vector<sf::Sprite> sprites);
};

