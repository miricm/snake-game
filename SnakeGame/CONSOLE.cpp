#include <iostream>
#include "CONSOLE.h"

void CONSOLE::init()
{
	// init handle
	h_console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!h_console) throw "ERROR GETTING CONSOLE HANDLE!";

	// init cursor
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	GetConsoleScreenBufferInfo(h_console, &info);

	cursor_pos = info.dwCursorPosition;
}

void CONSOLE::write_at_coord(int x, int y, char c)
{
	cursor_pos.X = x;
	cursor_pos.Y = y;

	SetConsoleCursorPosition(h_console, cursor_pos);

	if (c == '*' || c == ' ')
	{
		std::cout << c;
	}

	else throw "INVALID CHARACTER, ONLY ' ' AND '*' SUPPORTED!";	
}

void CONSOLE::destroy_handle(const HANDLE& h)
{
	CloseHandle(h);
}