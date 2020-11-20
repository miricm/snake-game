#include <iostream>
#include <future>
#include <conio.h>
#include "Game.h"
#include "Board.h"
#include "CONSOLE.h"

#define _PAUSE_TIME 100
#define KEY_UP       72
#define KEY_DOWN     80
#define KEY_LEFT     75
#define KEY_RIGHT    77
#define KEY_ESC      27


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
	board[2][2] = '*';
	board[2][3] = '*';

	CONSOLE::write_at_coord(2, 2, '*');
	CONSOLE::write_at_coord(3, 2, '*');
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

	CONSOLE::write_at_coord(x, y, '*');
	board[y][x] = '*';
	snake->seq.push({ y, x });
}

void Game::move_tail()
{
	// tail coordinates
	int x = snake->seq.front().second;
	int y = snake->seq.front().first;

	CONSOLE::write_at_coord(x, y, ' ');

	board[y][x] = ' ';
	snake->seq.pop();
}

std::future<int> Game::start_key_press_task()
{
	return std::async(std::launch::async, []
	{
		// return method for getting input
		return _getch();
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
	int game_is_running = true;

	while (game_is_running)
	// game loop
	{
		Sleep(_PAUSE_TIME);

		// check again
		if (f.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
		{			
			switch (f.get())
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

		this->move_snake(dir);
	}
}