#include "GameFunct.h"
 
void setConsoleColor(int background, int text) 
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    WORD color = (WORD)((background << 4) | text);
    DWORD written;

    FillConsoleOutputAttribute(hStdOut, color, consoleSize, { 0, 0 }, &written);
    FillConsoleOutputCharacter(hStdOut, ' ', consoleSize, { 0, 0 }, &written);
    SetConsoleCursorPosition(hStdOut, { 0, 0 });
    SetConsoleTextAttribute(hStdOut, color);
}

void setConsoleFontSize(int fontSize) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };

    // �������� ������� ��������� ������ �������
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    // ������������� ����� ������ ������ (������)
    fontInfo.dwFontSize.Y = fontSize;

    // ��������� ���������
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

int main()
{ 
    setConsoleColor(15, 0);
    setConsoleFontSize(20);

	Game game;
	game.run();
}