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
		default:
			break;
		}
	}
}

sf::Vector2i Viewer::getMousePosition()
{
	return sf::Mouse::getPosition(*this->window);
}

void Viewer::close()
{
	this->window->close();
}

void Viewer::update()
{
	pollevent();
}

void Viewer::clear()
{
	this->window->clear(sf::Color::White);
}

int Viewer::showMenu()	//0:exit game 1:start new game 2:select a file
{
	int choice=-1;
	//title
	sf::Text title(L"中國象棋", font);
	title.setCharacterSize(120);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::Black);
	title.setPosition(sf::Vector2f(400.f, 100.f));
	this->window->draw(title);

	//button
	sf::Text startText(L"開始遊戲", font);
	startText.setCharacterSize(60);
	startText.setFillColor(sf::Color::Black);
	startText.setPosition(sf::Vector2f(520.f, 350.f));
	sf::RectangleShape startBtn(sf::Vector2f(260.f, 70.f));
	startBtn.setPosition(sf::Vector2f(510.f, 355.f));
	startBtn.setOutlineThickness(1);
	startBtn.setOutlineColor(sf::Color(0, 0, 0, 255));
	startBtn.setFillColor(sf::Color(0, 0, 0, 50));

	sf::Text fileText(L"讀取資料", font);
	fileText.setCharacterSize(60);
	fileText.setFillColor(sf::Color::Black);
	fileText.setPosition(sf::Vector2f(520.f, 450.f));
	sf::RectangleShape fileBtn(sf::Vector2f(260.f, 70.f));
	fileBtn.setPosition(sf::Vector2f(510.f, 455.f));
	fileBtn.setOutlineThickness(1);
	fileBtn.setOutlineColor(sf::Color(0, 0, 0, 255));
	fileBtn.setFillColor(sf::Color(0, 0, 0, 50));

	sf::Text exitText(L"離開遊戲", font);
	exitText.setCharacterSize(60);
	exitText.setFillColor(sf::Color::Black);
	exitText.setPosition(sf::Vector2f(520.f, 550.f));
	sf::RectangleShape exitBtn(sf::Vector2f(260.f, 70.f));
	exitBtn.setPosition(sf::Vector2f(510.f, 555.f));
	exitBtn.setOutlineThickness(1);
	exitBtn.setOutlineColor(sf::Color(0, 0, 0, 255));
	exitBtn.setFillColor(sf::Color(0, 0, 0, 50));

	sf::FloatRect startRect(startBtn.getPosition(), startBtn.getSize());
	sf::FloatRect fileRect(fileBtn.getPosition(), fileBtn.getSize());
	sf::FloatRect exitRect(exitBtn.getPosition(), exitBtn.getSize());

	if (startRect.contains(sf::Vector2f(this->getMousePosition())))
	{
		startBtn.scale(sf::Vector2f(1.05, 1.05));
		startBtn.setPosition(sf::Vector2f(510-6.5, 355-1.75));
		choice = 1;
	}
	else
	{
		startBtn.scale(sf::Vector2f(1, 1));
		startBtn.setPosition(sf::Vector2f(510, 355));
	}

	if (fileRect.contains(sf::Vector2f(this->getMousePosition())))
	{
		fileBtn.scale(sf::Vector2f(1.05, 1.05));
		fileBtn.setPosition(sf::Vector2f(510 - 6.5, 455 - 1.75));
		choice = 2;
	}
	else
	{
		fileBtn.scale(sf::Vector2f(1, 1));
		fileBtn.setPosition(sf::Vector2f(510, 455));
	}

	if (exitRect.contains(sf::Vector2f(this->getMousePosition())))
	{
		exitBtn.scale(sf::Vector2f(1.05, 1.05));
		exitBtn.setPosition(sf::Vector2f(510 - 6.5, 555 - 1.75));
		choice = 0;
	}
	else
	{
		exitBtn.scale(sf::Vector2f(1, 1));
		exitBtn.setPosition(sf::Vector2f(510, 555));
	}
	
	
	this->window->draw(startBtn);
	this->window->draw(startText);
	this->window->draw(fileBtn);
	this->window->draw(fileText);
	this->window->draw(exitBtn);
	this->window->draw(exitText);
	
	return choice;
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
	//show who win
	sf::Text win;
	if (team == Team::Red) 
		win.setString(L"紅方獲勝!!");
	else
		win.setString(L"黑方獲勝!!");
	win.setFont(font);
	win.setCharacterSize(80);
	win.setStyle(sf::Text::Bold);
	win.setFillColor(sf::Color::Black);
	win.setPosition(sf::Vector2f(700.f,100.f));
	this->window->draw(win);

	

}

int Viewer::showOneMoreGame()
{
	int choice = -1;
	//show one more game
	sf::Text oneMore(L"再來一局?", font);
	oneMore.setCharacterSize(50);
	oneMore.setFillColor(sf::Color::Black);
	oneMore.setPosition(sf::Vector2f(700.f, 300.f));
	this->window->draw(oneMore);

	//show botton
	sf::Text yesText(L"是", font);
	sf::Text noText(L"否", font);

	yesText.setCharacterSize(40);
	yesText.setFillColor(sf::Color::Black);
	yesText.setPosition(sf::Vector2f(730.f, 400.f));

	noText.setCharacterSize(40);
	noText.setFillColor(sf::Color::Black);
	noText.setPosition(sf::Vector2f(850.f, 400.f));

	sf::RectangleShape yesBtn(sf::Vector2f(100, 60));
	sf::RectangleShape noBtn(sf::Vector2f(100, 60));
	yesBtn.setPosition(sf::Vector2f(700, 400));
	noBtn.setPosition(sf::Vector2f(820, 400));
	yesBtn.setOutlineThickness(1);
	noBtn.setOutlineThickness(1);
	yesBtn.setOutlineColor(sf::Color(0, 0, 0, 255));
	noBtn.setOutlineColor(sf::Color(0, 0, 0, 255));
	yesBtn.setFillColor(sf::Color(0, 0, 0,50));
	noBtn.setFillColor(sf::Color(0, 0, 0, 50));
	
	sf::FloatRect yesRect(yesBtn.getPosition(), yesBtn.getSize()), noRect(noBtn.getPosition(), noBtn.getSize());
	
	if (yesRect.contains(sf::Vector2f(this->getMousePosition()))) {
		yesBtn.scale(sf::Vector2f(1.05, 1.05));
		yesBtn.setPosition(sf::Vector2f(700-1, 400-0.6));
		choice = 1;
	}
	else {
		yesBtn.scale(sf::Vector2f(1.f, 1.f));
		yesBtn.setPosition(sf::Vector2f(700, 400));
	}

	if (noRect.contains(sf::Vector2f(this->getMousePosition()))) {
		noBtn.scale(sf::Vector2f(1.05, 1.05));
		noBtn.setPosition(sf::Vector2f(820 - 1, 400 - 0.6));
		choice = 0;
	}
	else {
		noBtn.scale(sf::Vector2f(1.f, 1.f));
		noBtn.setPosition(sf::Vector2f(820, 400));
	}

	this->window->draw(yesBtn);
	this->window->draw(noBtn);
	this->window->draw(yesText);
	this->window->draw(noText);
	return choice;
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