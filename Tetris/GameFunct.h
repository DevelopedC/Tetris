#pragma once

#include<iostream>
#include<vector>

#include<windows.h>
#include<conio.h>

#include "Figure.h"
#include "MapFunct.h"

using std::cout;
using std::endl;
using std::vector;
 
constexpr int ArrowRight = 77;
constexpr int ArrowLeft = 75;
constexpr int ArrowUP = 72;
constexpr int ArrowDown = 80;
constexpr int Space = 32;

class Game
{
private:
	Figure fig;
	Map map;

	const int SleepGameOver = 100;
	const int ArrowButtons = 224;
	const int SleepMainLoop = 50;
	const int HEIGHT = 15;
	const int WHITE = 15;
	const int RED = 4;

	inline void gameOver();
	inline void hideCursor();
	inline void MoveArrowRight();
	inline void MoveArrowDown();
	inline void MoveArrowLeft();
	inline void MoveArrowUP();
	inline void MoveSpace();

public:
	Game();
	int run();
};
 