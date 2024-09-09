#include "MapFunct.h"
 
Map::Map(Figure& F_ptr) : ptr(F_ptr), figVec(F_ptr.get_figVec())
{
	show_res(NULL);
}

inline void Map::show_res(int count)
{
	// show score
	switch (count)
	{
	case 1:
		score += 5;
		break;

	case 2:
		score += 10;
		break;

	case 3:
		score += 15;
		break;

	default:
		if (count > 4)
			score += 25;
		break;
	}

	gotoxy(2, 17);
	cout << "SCORE: " << score;
}

// checking if the figure is out of range
bool Map::isCollision()
{
	for (int i = 0; i < figVec.size(); ++i)
	{
		if (figVec[i].y < 0) // collision with the upper boundary
			return true;

		if (figVec[i].x <= 0) // collision with the left boundary
			return true;

		if (figVec[i].x >= WIDTH - 1) // collision with the right boundary
			return true;
		 
		// border collision
		if (fieldVec[figVec[i].y][figVec[i].x] == BORDER)
			return true;
		// collision with an established figure
		if (fieldVec[figVec[i].y][figVec[i].x] == BLOCK)
			return true;
	}
	return false;
}

// fixing the figure that bottomed out
void Map::fixed()
{
	for (int i = 0; i < figVec.size(); ++i)
		fieldVec[figVec[i].y][figVec[i].x] = BLOCK;
}

// creation of a new figure
void Map::spawn()
{
	figVec.clear();
	srand(time(nullptr));
	ptr.get_kind() = rand() % 7;
	switch (ptr.get_kind())
	{
	case 0: // square
		ptr.push(4, 0);	 // * * 
 		ptr.push(5, 0);  // * * 
		ptr.push(4, 1);
		ptr.push(5, 1);  
	break;
	
	case 1: // line
		ptr.push(4, 0); // * * * *
		ptr.push(5, 0);
		ptr.push(6, 0);
		ptr.push(7, 0);
	break;

	case 2: // letter L1
		ptr.push(4, 0);  // * * * 
		ptr.push(5, 0);	 //     * 
		ptr.push(6, 0);  
		ptr.push(6, 1);
	break;

	case 3: // letter L2
		ptr.push(4, 0);  // * * * 
		ptr.push(5, 0);	 // * 
		ptr.push(6, 0);
		ptr.push(4, 1);
	break;

	case 4: // letter Z1		
		ptr.push(4, 0);  // * * 
		ptr.push(5, 0);	 //   * *
		ptr.push(5, 1);
		ptr.push(6, 1);
	break;

	case 5: // letter Z2		
		ptr.push(4, 1);  //   * * 
		ptr.push(5, 1);	 // * *
		ptr.push(5, 0);
		ptr.push(6, 0);
	break;

	case 6: // letter T		
		ptr.push(4, 1);  //   * 
		ptr.push(5, 1);	 // * * *
		ptr.push(6, 1);
		ptr.push(5, 0);
	break;
	}
}

void Map::animDeleteLines(const vector<int> &dellines)
{
	if (dellines.empty())
		return;

	for (int i = 1; i <= WIDTH-2; i++)
	{
		for (int j = 0; j < dellines.size(); j++)
		{
			gotoxy(i, dellines[j]);
			cout << " ";
		}
		Sleep(SLEEP_ANIM_DEL_LINES);
	}
}

// deleting the line at the bottom
void Map::deleteLines()
{
	vector<int> dellines;

	// identifying rows to be removed
	for (int i = fieldVec.size() - 2; i >= 0; --i)
	{
		int count = 0;
		for (int j = 1; j < fieldVec[i].size() - 1; ++j)
		{
			if (fieldVec[i][j] == BLOCK) { count++; }
			else { break; }
		}
		if (count == WIDTH-2)
		{
			dellines.push_back(i);
		}
	}
	 
	show_res(dellines.size());

	animDeleteLines(dellines);

	// deleting rows that have overlapped
	for (int i = 0; i < dellines.size(); i++)
		fieldVec.erase(fieldVec.begin() + dellines[i]);

	// adding empty rows on top instead of deleted ones
	vector<int> temp;

	temp.push_back(BORDER);
	for (int i = 1; i < WIDTH - 1; i++)
		temp.push_back(EMPTY);
	temp.push_back(BORDER);


	for (auto& el : dellines)
		fieldVec.insert(fieldVec.begin(), temp);
}

// initialize the playing field
void Map::initVec()
{
	vector<int> temp;

	temp.push_back(BORDER);
	for (int i = 1; i < WIDTH - 1; i++)
		temp.push_back(EMPTY);
	temp.push_back(BORDER);


	for (int i = 0; i < HEIGHT - 1; i++)
		fieldVec.push_back(temp);

	temp.clear();
	for (int i = 0; i < WIDTH; i++)
		temp.push_back(BORDER);

	fieldVec.push_back(temp);
}

// draw a field
void Map::showField()
{
	// map drawing
	gotoxy(0, 0);
	for (int i = 0; i < fieldVec.size(); ++i)
	{
		for (int j = 0; j < fieldVec[i].size(); ++j)
			if (fieldVec[i][j] == BORDER)
				cout << "#";
			else if (fieldVec[i][j] == BLOCK)
				cout << char(6);	 
			else if (fieldVec[i][j] == EMPTY)
				cout << ' ';

		cout << endl;
	}
}
 
// set a new cursor position on the screen
void gotoxy(short x, short y)
{
	COORD p = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
  
bool Map::shiftLeftFig()
{
	if (isCollision())
	{
		ptr.moveLeft();
		if (isCollision())
		{
			ptr.moveLeft();
			if (isCollision())
			{
				return false;
			}
		}
	}
	return true;
}

bool Map::shiftRightFig()
{
	if (isCollision())
	{
		ptr.moveRight();
		if (isCollision())
		{
			ptr.moveRight();
			if (isCollision())
			{
				return false;
			}
		}
	}
	return true;
}

 