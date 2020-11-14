#pragma once
#include <Windows.h>

static class CONSOLE
{
public: 
	static COORD get_cursor_position(const HANDLE& h);
	static HANDLE get_console_handle();
	static void destroy_handle(const HANDLE& h);
};