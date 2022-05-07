#pragma once
#include <vector>
#include "GameHeader.h"
#include "Chess.h"

#define CHECKBOARD "./Asset/Image/Checkboard/Checkboard.jpg"


class Board
{
private:
	std::vector<std::vector<Chess*>> boardArr;
	sf::Texture checkBoardTexture;
	sf::Sprite cheakBoard;

public:
	Board();
	sf::Sprite& getSprite();
};

