#include "GameFunct.h"
 
Game::Game() : fig(), map(fig)
{
	map.initVec();
	map.showField();

	map.spawn();
	fig.show();

	this->hideCursor();
}

// game start
int Game::run()
{
	int ch = 0;
 
	while (true)
	{
		//if the key is not pressed
		while (!_kbhit())
		{
			fig.hide();
			
			if(map.ptr.allowMove())
				fig.moveDown();
			
			if (map.isCollision())
			{
				fig.moveUp();
				map.fixed();
				map.deleteLines();
				map.showField();
				map.spawn();
				// ñhecking for the end of the game
				if (map.isCollision())
				{
					fig.show();
					this->gameOver();
					return 0;
				}
			}

			fig.show();
			Sleep(SleepMainLoop);
		}

		ch = _getch();
		 
		// key processing
		switch (ch)
		{
		case ArrowRight:
			MoveArrowRight();
		break;

		case ArrowDown:
			MoveArrowDown();
		break;

		case ArrowLeft:
			MoveArrowLeft();
		break;

		case ArrowUP: // rotate clockwise the shape
			MoveArrowUP();
		break;

		case Space: // counterclockwise
			MoveSpace();
		break;

		}
		fig.show();
	}

	return 0;
}
 
inline void Game::gameOver()
{
	fig.setColor(WHITE, RED);
	for (size_t i = 0; i < HEIGHT; i++)
	{
		gotoxy(1, i);
		Sleep(SleepGameOver);

		if (i == HEIGHT/2)
			cout << "GAME-OVER ";
		else
			cout << "XXXXXXXXXX";
	}
	cout << "\n\n";
}

inline void Game::hideCursor()
{
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

inline void Game::MoveArrowRight()
{
	fig.hide();
	fig.moveRight();

	if (map.isCollision())
		fig.moveLeft();
}

inline void Game::MoveArrowDown()
{
	fig.hide();
	fig.moveDown();

	if (map.isCollision())
		fig.moveUp();
}

inline void Game::MoveArrowLeft()
{
	fig.hide();
	fig.moveLeft();

	if (map.isCollision())
		fig.moveRight();
}

inline void Game::MoveArrowUP()
{
	fig.hide();
	fig.save();

	fig.rotateR();
	if (!map.shiftLeftFig())
	{
		fig.undo();
		fig.rotateR();
		if (!map.shiftRightFig())
			fig.undo();
	}
}

inline void Game::MoveSpace()
{
	fig.hide();
	fig.save();

	fig.rotateL();
	if (!map.shiftLeftFig())
	{
		fig.undo();
		fig.rotateL();
		if (!map.shiftRightFig())
			fig.undo();
	}
}
