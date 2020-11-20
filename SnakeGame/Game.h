#pragma once
#include <future>
#include "Snake.h"
#include "Direction.h"

class Game
{
private:
	char** board;
	Snake* snake;

	void show_board();
	void init_snake();	
	void move_snake(Direction dir);

	void move_tail();
	std::future<int> start_key_press_task();
	// int move_head(Direction dir);
public:
	Game();
	void start_game();
	// void end_game();
};

