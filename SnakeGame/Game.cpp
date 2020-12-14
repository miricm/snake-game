#include <iostream>
#include <future>
#include <conio.h>
#include <ctime>
#include "Game.h"
#include "Board.h"
#include "CONSOLE.h"

#define _PAUSE_TIME   20
#define KEY_UP        72
#define KEY_DOWN      80
#define KEY_LEFT      75
#define KEY_RIGHT     77
#define KEY_ESC       27

#define _EMPTY       ' '
#define _FILLED      '*'


Game::Game()
{
	this->board = Board::create_board();
	this->snake = new Snake;
}

void Game::show_board()
{
	for (size_t i = 0; i < Board::HEIGHT; i++)
	{
		for (size_t j = 0; j < Board::WIDTH; j++)
		{
			std::cout << board[i][j];
		}

		std::cout << "\n";
	}
}

void Game::init_snake()
{
	snake->seq.push({ 2,2 }); // front
	snake->seq.push({ 2,3 }); // back

	// fill the board object	
	board[2][2] = _FILLED;
	board[2][3] = _FILLED;

	CONSOLE::write_at_coord(2, 2, _FILLED);
	CONSOLE::write_at_coord(3, 2, _FILLED);
}

void Game::move_snake(Direction dir)
{
	// TODO: hide cursor
	this->move_tail();

	int x = 0, y = 0;

	// switch for new head coordinates
	switch (dir)
	{
	case Direction::UP: {
		x = snake->seq.back().second;
		y = snake->seq.back().first - 1;
		break;
	}
	case Direction::DOWN: {
		x = snake->seq.back().second;
		y = snake->seq.back().first + 1;
		break;
	}
	case Direction::RIGHT: {
		x = snake->seq.back().second + 1;
		y = snake->seq.back().first;
		break;
	}
	case Direction::LEFT: {
		x = snake->seq.back().second - 1;
		y = snake->seq.back().first;
		break;
	}
	}

	CONSOLE::write_at_coord(x, y, _FILLED);
	board[y][x] = _FILLED;
	snake->seq.push({ y, x });
}

void Game::move_tail()
{
	// tail coordinates
	int x = snake->seq.front().second;
	int y = snake->seq.front().first;

	CONSOLE::write_at_coord(x, y, _EMPTY);

	board[y][x] = _EMPTY;
	snake->seq.pop();
}

std::future<int> Game::start_key_press_task()
{
	return std::async(std::launch::async, []
	{
		// return method for getting input
		int get = _getch();
		if(get == 0 || get == 224) 
		{
			return _getch();
		}

		return get;
	});
}

void Game::start_game()
{
	this->show_board();

	// init console
	CONSOLE::init();

	// set inital snake position
	this->init_snake();

	// start parallel task
	auto f = start_key_press_task();

	Direction dir = Direction::RIGHT; // starting direction of the snake
	bool game_is_running = true;

	while (game_is_running)
	// game loop
	{
		this->move_snake(dir);

		Sleep(_PAUSE_TIME);

		if (f.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
		{
			int key = f.get();

			switch (key)
			{
			case KEY_UP:
				dir = Direction::UP;
				break;
			case KEY_DOWN:
				dir = Direction::DOWN;
				break;
			case KEY_LEFT:
				dir = Direction::LEFT;
				break;
			case KEY_RIGHT:
				dir = Direction::RIGHT;
				break;
			case KEY_ESC:
				game_is_running = false;
				break;
			}			
			// run parallel again
			f = start_key_press_task();			
		}						
	}
}