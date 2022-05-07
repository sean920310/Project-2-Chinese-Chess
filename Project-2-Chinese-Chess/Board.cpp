#include "Board.h"

Board::Board()
{
	checkBoardTexture.loadFromFile(CHECKBOARD);
	cheakBoard.setTexture(checkBoardTexture);
	cheakBoard.setPosition(sf::Vector2f(35.0625f, 58.05f));
	cheakBoard.setScale(sf::Vector2f(CHECKBOARD_SCALE_SIZE, CHECKBOARD_SCALE_SIZE));
}

sf::Sprite& Board::getSprite()
{
	return cheakBoard;
}


