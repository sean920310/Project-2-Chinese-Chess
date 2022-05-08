#include "Viewer.h"


Viewer::Viewer() : ev()
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

sf::Vector2i Viewer::getMousePosition()
{
	return sf::Mouse::getPosition(*this->window);
}

void Viewer::update()
{
	pollevent();
	//**update

	/*for (auto& chess : allChess) {
		chess->showSelect(sf::Mouse::getPosition(*this->window), currentPlayer);
	}*/


}

void Viewer::clear()
{
	this->window->clear(sf::Color::White);
}

void Viewer::drawCanMovePos(std::vector<Coord> coords)
{
	for (auto coord : coords) {
		sf::CircleShape circle(30.3);
		float x, y;
		x = CHECKBOARD_SCALE_SIZE * (coord.x * 233.75 + 34) + 35.0625 - CHESS_SCALE_SIZE * (606.0 / 2);
		y = CHECKBOARD_SCALE_SIZE * (coord.y * 233.75 + 34) + 58.05 - CHESS_SCALE_SIZE * (606.0 / 2);
		circle.setPosition(x, y);
		circle.setFillColor(sf::Color(255, 0, 0, 127));
		this->window->draw(circle);
	}
}

void Viewer::drawSprite(std::vector<sf::Sprite> sprites)
{
	//draw
	for (const auto& sprite : sprites)
		this->window->draw(sprite);

}

void Viewer::display()
{
	this->window->display();
}