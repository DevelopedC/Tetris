#pragma once

#include<iostream>
#include<vector>
  
using std::cout;
using std::vector;

// coordinates
struct Point
{
	int x;
	int y;
};

class Figure
{
private:
	const int COUNT_TACT_FOR_NOT_MOVE_FIGURE = 5;

	vector<Point> figVec;
	vector<Point> bVec; // to save and roll back
	
	int countTact = 0;
	int kind = 0;

 public:
	 enum ConsoleColor;
	 vector<Point>& get_figVec();

	 void setColor(int background, int text);

	 void push(int x, int y);
	 void show();
	 void hide();

	 void moveUp();
	 void moveDown();
	 void moveLeft();
	 void moveRight();
	  
	 void rotateR();
	 void rotateL();

	 void save();
	 void undo();

	 bool allowMove();

	 int& get_kind();
};