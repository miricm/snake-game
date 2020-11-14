#pragma once
#include <Windows.h>

static COORD cursor_pos;
static HANDLE h_console;

static class CONSOLE
{
public: 
	static void init();
	static void write_at_coord(int x, int y, char c);
	static void destroy_handle(const HANDLE& h);
};