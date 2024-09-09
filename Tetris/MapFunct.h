#pragma once

#include<iostream>
#include<vector>

#include<windows.h>
#include<conio.h>

#include "Figure.h"

using std::cout;
using std::endl;
using std::vector;

class Map
{
private:
	vector<vector<int>> fieldVec;
	int score = 0;

	// field size
	const int WIDTH = 10 + 2;
	const int HEIGHT = 15 + 1;
	const int SLEEP_ANIM_DEL_LINES = 50;

	// constant map values
	const int EMPTY = 0;
	const int BORDER = 1;
	const int BLOCK = 2;
	 
public:
	Map(Figure& F_ptr);

	Figure& ptr;
	vector<Point>& figVec;

	bool isCollision();
	 
	void fixed();
	void spawn();
	void animDeleteLines(const vector<int>& dellines);
	void deleteLines();
	inline void show_res(int count);
	
	void initVec();
	void showField();
	bool shiftLeftFig();
	bool shiftRightFig();
};

extern void gotoxy(short x, short y);