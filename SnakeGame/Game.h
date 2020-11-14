#pragma once
#include <queue>
#include "Snake.h"
#include "Direction.h"
#include <Windows.h>

class Game
{
private:
	char** board;
	Snake* snake;
	void show_board();
	void init_snake(COORD& cursor_pos, const HANDLE& console);	
	void move_snake(COORD& cursor_pos, const HANDLE& console, Direction dir);
public:
	Game();
	void start_game();
	// void end_game();
};

