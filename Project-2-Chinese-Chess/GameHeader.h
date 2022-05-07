#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#define CHESS_KING_BLACK     "./Asset/Image/Chess/Chess_King_Black.png"
#define CHESS_ADVISORS_BLACK "./Asset/Image/Chess/Chess_Advisors_Black.png"
#define CHESS_MINISTER_BLACK "./Asset/Image/Chess/Chess_Minister_Black.png"
#define CHESS_CHARIOTS_BLACK "./Asset/Image/Chess/Chess_Chariots_Black.png"
#define CHESS_KNIGHTS_BLACK  "./Asset/Image/Chess/Chess_Knights_Black.png"
#define CHESS_CANNONS_BLACK  "./Asset/Image/Chess/Chess_Cannons_Black.png"
#define CHESS_SOLDIERS_BLACK "./Asset/Image/Chess/Chess_Soldiers_Black.png"

#define CHESS_KING_RED     "./Asset/Image/Chess/Chess_King_Red.png"
#define CHESS_ADVISORS_RED "./Asset/Image/Chess/Chess_Advisors_Red.png"
#define CHESS_MINISTER_RED "./Asset/Image/Chess/Chess_Minister_Red.png"
#define CHESS_CHARIOTS_RED "./Asset/Image/Chess/Chess_Chariots_Red.png"
#define CHESS_KNIGHTS_RED  "./Asset/Image/Chess/Chess_Knights_Red.png"
#define CHESS_CANNONS_RED  "./Asset/Image/Chess/Chess_Cannons_Red.png"
#define CHESS_SOLDIERS_RED "./Asset/Image/Chess/Chess_Soldiers_Red.png"

#define CHECKBOARD "./Asset/Image/Checkboard/Checkboard.jpg"

#define CHESS_SCALE_SIZE 0.1f
#define CHECKBOARD_SCALE_SIZE 0.3f

enum class Characters
{
	King,
	Advisors,
	Minister,
	Chariots,
	Knights,
	Cannons,
	Soldiers,
};

enum class Team
{
	Red,
	Black
};
