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

void Viewer::update(std::vector<Chess*> allChess)
{
	pollevent();
	//**update
	//	-show if chess is select

	for (auto& chess : allChess) {
		chess->showSelect(sf::Mouse::getPosition(*this->window));
	}


}

void Viewer::render(std::vector<sf::Sprite> sprites)
{

	this->window->clear(sf::Color::White);
	//draw
	for (const auto& sprite : sprites)
		this->window->draw(sprite);

	this->window->display();
}
