#pragma once
#include <future>
#include "Snake.h"
#include "Direction.h"
#include "CollisionType.h"

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

	void generate_food();

	CollisionType detect_collision(const Direction& dir);

public:
	Game();
	~Game();
	void start_game();
	// void end_game();
};

