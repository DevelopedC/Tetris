#include "Figure.h"
#include "MapFunct.h"


enum Figure::ConsoleColor
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GRAY = 7,
	DARKGRAY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MEGENTA = 13,
	YELLOW = 14,
	WHITE = 15,
};

void Figure::setColor(int background, int text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void Figure::push(int x, int y)
{
	figVec.push_back(Point{ x,y });
}

void Figure::show()
{
	switch (kind)
	{
	case 0:
		setColor(WHITE, BLUE);
		break;
	case 1:
		setColor(WHITE, GREEN);
		break;
	case 2:
		setColor(WHITE, RED);
		break;
	case 3:
		setColor(WHITE, RED);
		break;
	case 4:
		setColor(WHITE, BROWN);
		break;
	case 5:
		setColor(WHITE, BROWN);
		break;
	case 6:
		setColor(WHITE, MAGENTA);
		break;
	}
	 
	for (auto &it : figVec)
	{
		gotoxy(it.x, it.y);
		cout << char(4);// ANSI code
	}
	setColor(WHITE, BLACK);
}

void Figure::hide()
{
	for (auto& it : figVec)
	{
		gotoxy(it.x, it.y);
		cout << ' ';
	}
}

void Figure::moveUp()
{
	for (auto& it : figVec)
		it.y--;
}

void Figure::moveDown()
{
	for (auto& it : figVec)
	  it.y++;
}

void Figure::moveLeft()
{
	for (auto& it : figVec)
		it.x--;
}

void Figure::moveRight()
{
	for (auto& it : figVec)
		it.x++;
}

vector<Point>& Figure::get_figVec()
{
	return figVec;
}

void Figure::save()
{
	bVec = figVec;
}

void Figure::undo()
{
	figVec = bVec;
}

// figure rotation algorithm
void Figure::rotateR()
{ 
	for (int i = 0; i < figVec.size(); i++)
	{
		int x = -(figVec[i].y - figVec[1].y) + figVec[1].x;
		int y =  (figVec[i].x - figVec[1].x) + figVec[1].y;
		figVec[i].x = x;
		figVec[i].y = y;
	}
}

void Figure::rotateL()
{
	for (int i = 0; i < figVec.size(); i++)
	{
		int x = (figVec[i].y - figVec[1].y) + figVec[1].x;
		int y = -(figVec[i].x - figVec[1].x) + figVec[1].y;
		figVec[i].x = x;
		figVec[i].y = y;
	}
}
 
bool Figure::allowMove()
{
	if (countTact < COUNT_TACT_FOR_NOT_MOVE_FIGURE)
	{
		countTact++;
		return false;
	}
	countTact = 0;
	return true;
}

int& Figure::get_kind()
{
	return kind;
}