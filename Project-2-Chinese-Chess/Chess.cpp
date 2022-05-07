#include "Chess.h"

Chess::Chess(const Team& team)
{
	this->team = team;
}

sf::Sprite Chess::getSprite()
{
	return sf::Sprite();
}


King::King(const Team& team):Chess(team)
{
	if(team==Team::Black)
		chessTexture.loadFromFile(CHESS_KING_BLACK);
	else
		chessTexture.loadFromFile(CHESS_KING_RED);
	chess.setTexture(chessTexture);
	chess.setPosition(sf::Vector2f(295.1625, 37.05f));
	chess.setScale(sf::Vector2f(CHESS_SCALE_SIZE, CHESS_SCALE_SIZE));
}

void King::move() 
{
	return;
}

sf::Sprite King::getSprite()
{
	return this->chess;
}
