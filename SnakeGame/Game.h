#pragma once
#include <queue>
#include "Snake.h"
#include "Direction.h"
#include <Windows.h>

class Game
{
private:
	// Console handles
	COORD  cursor_pos;
	HANDLE h_console;

	char** board;
	Snake* snake;

	void show_board();
	void init_snake(COORD& cursor_pos, const HANDLE& console);	
	void move_snake(COORD& cursor_pos, const HANDLE& console, Direction dir);

	void move_tail(COORD& cursor_pos, const HANDLE& console);
	// int move_head(COORD& cursor_pos, const HANDLE& console, Direction dir);
public:
	Game(const COORD& cursor_pos, const HANDLE& h_console);
	void start_game();
	// void end_game();
};

