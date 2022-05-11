#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#define CHESS_GENERAL_BLACK     "./Asset/Image/Chess/Chess_General_Black.png"
#define CHESS_ADVISOR_BLACK "./Asset/Image/Chess/Chess_Advisor_Black.png"
#define CHESS_ELEPHANT_BLACK "./Asset/Image/Chess/Chess_Elephant_Black.png"
#define CHESS_HORSE_BLACK "./Asset/Image/Chess/Chess_Horse_Black.png"
#define CHESS_CHARIOT_BLACK  "./Asset/Image/Chess/Chess_Chariot_Black.png"
#define CHESS_CANNON_BLACK  "./Asset/Image/Chess/Chess_Cannon_Black.png"
#define CHESS_SOLDIER_BLACK "./Asset/Image/Chess/Chess_Soldier_Black.png"

#define CHESS_GENERAL_RED     "./Asset/Image/Chess/Chess_General_Red.png"
#define CHESS_ADVISOR_RED "./Asset/Image/Chess/Chess_Advisor_Red.png"
#define CHESS_ELEPHANT_RED "./Asset/Image/Chess/Chess_Elephant_Red.png"
#define CHESS_HORSE_RED "./Asset/Image/Chess/Chess_Horse_Red.png"
#define CHESS_CHARIOT_RED  "./Asset/Image/Chess/Chess_Chariot_Red.png"
#define CHESS_CANNON_RED  "./Asset/Image/Chess/Chess_Cannon_Red.png"
#define CHESS_SOLDIER_RED "./Asset/Image/Chess/Chess_Soldier_Red.png"

#define CHECKBOARD "./Asset/Image/Checkboard/Checkboard.jpg"

#define FONT_PATH "./Asset/Font/kaiu.ttf"

#define CHESS_SCALE_SIZE 0.1f
#define CHESS_CHOISE_SCALE_SIZE 0.108f
#define CHECKBOARD_SCALE_SIZE 0.3f

enum class Characters
{
	General,
	Advisor,
	Elephant,
	Horse,
	Chariot,
	Cannon,
	Soldier,
};

enum class Team
{
	Red,
	Black
};

enum class InGameState
{
	start,
	inputFile,
	selectChess,
	pressChess,
	choiceMove,
	isCheck,
	oneSideWin
};

typedef struct Coord {
	int x;
	int y;

	Coord():x(0),y(0)
	{
	}

	Coord(int x, int y):x(x),y(y)
	{
	}

	Coord(const Coord& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
	}

	Coord& operator=(const Coord& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}

	bool operator==(const Coord& rhs) {
		return (this->x == rhs.x && this->y == rhs.y);
	}
}Coord;

#define WIN32_LEAN_AND_MEAN
#include <shobjidl.h> 
#include <windows.h>

