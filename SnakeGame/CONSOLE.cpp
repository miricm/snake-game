#include "CONSOLE.h"

COORD CONSOLE::get_cursor_position(const HANDLE& h)
{
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	GetConsoleScreenBufferInfo(h, &info);

	return info.dwCursorPosition;
}

HANDLE CONSOLE::get_console_handle()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!h) throw "ERROR GETTING CONSOLE HANDLE!";
	
	return h;
}

void CONSOLE::destroy_handle(const HANDLE& h)
{
	CloseHandle(h);
}