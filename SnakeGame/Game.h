#pragma once
#include <queue>
#include "Snake.h"

class Game
{
private:
	char** board;
	Snake* snake;

public:
	Game();
	void show_board();
	void start_game();
};

