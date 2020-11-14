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

public:
	Game();
	void show_board();
	void init_snake(COORD& cursor_pos, const HANDLE& console);

	void start_game();
	void move_snake(COORD& cursor_pos, const HANDLE& console, Direction dir);

	// void end_game();
};

