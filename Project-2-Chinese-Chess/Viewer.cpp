#include "Viewer.h"

#define ADVISORS_BLACK "./Asset/Image/Chess/Chess_Advisors_Black.png"
#define ADVISORS_RED "./Asset/Image/Chess/Chess_Advisors_Red.png"




Viewer::Viewer():board(), ev(),blackKing(Team::Black)
{
	this->videoMode.height = 768;
	this->videoMode.width = 1280;

	this->window = new sf::RenderWindow(this->videoMode, "Chinese Chess", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

Viewer::~Viewer()
{
	delete this->window;
}

bool Viewer::windowIsOpen()
{
	return this->window->isOpen();
}

void Viewer::pollevent()
{
	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				window->close();
			break;
		}
	}
}

void Viewer::update()
{
	pollevent();
	//update
}

void Viewer::render()
{
	
	this->window->clear(sf::Color::White);
	//draw
	//for (auto& sprite : sprites) {
	this->window->draw(this->board.getSprite());
	//}
	this->window->draw(this->blackKing.getSprite());
	this->window->display();
}
