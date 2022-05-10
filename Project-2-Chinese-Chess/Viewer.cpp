#include "Viewer.h"


Viewer::Viewer() : ev()
{
	this->videoMode.height = 768;
	this->videoMode.width = 1280;

	this->window = new sf::RenderWindow(this->videoMode, L"Chinese Chess中國象棋", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	
	font.loadFromFile(FONT_PATH);
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
}

void Viewer::clear()
{
	this->window->clear(sf::Color::White);
}

void Viewer::showCheck(Team team)
{
	if (team == Team::Red) {
		sf::Text redCheck(L"紅方將軍!!",font);
		redCheck.setCharacterSize(40);
		//redCheck.setStyle(sf::Text::Bold);
		redCheck.setFillColor(sf::Color::Black);
		redCheck.setPosition(sf::Vector2f(700.f, 382. + 60.f));
		this->window->draw(redCheck);
	}
	else
	{

		sf::Text blackCheck(L"黑方將軍!!", font);
		blackCheck.setCharacterSize(40);
		//blackCheck.setStyle(sf::Text::Bold);
		blackCheck.setFillColor(sf::Color::Black);
		blackCheck.setPosition(sf::Vector2f(700.f, .0 + 60.f));
		this->window->draw(blackCheck);
	}

}

void Viewer::showWinner(Team team)
{


}

void Viewer::drawRightSideObject(Team team)
{
	//draw text
	sf::Text red(L"紅方", font);
	red.setCharacterSize(50);
	red.setStyle(sf::Text::Bold);
	red.setFillColor(sf::Color::Red);

	sf::Text black(red);
	black.setString(L"黑方");
	black.setFillColor(sf::Color::Black);
	black.setPosition(sf::Vector2f(700.f, .0f));
	red.setPosition(sf::Vector2f(700.f, 382.f));
	this->window->draw(red);
	this->window->draw(black);

	//draw current player
	sf::CircleShape showCurrentTeam(10.f);
	showCurrentTeam.setFillColor(sf::Color::Red);
	if (team == Team::Red) {
		showCurrentTeam.setPosition(sf::Vector2f(660.f, 407.f));
	}
	else
	{
		showCurrentTeam.setPosition(sf::Vector2f(660.f, 25.f));
	}
	this->window->draw(showCurrentTeam);


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