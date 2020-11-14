#include <iostream>
#include "Game.h"
#include "Board.h"
#include "CONSOLE.h"

#define _PAUSE_TIME   100

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

	// switch for new head coordinates
	switch (dir)
	{
	case Direction::UP:
		break;
	case Direction::DOWN:
		break;
	case Direction::RIGHT: {
		int x = snake->seq.back().second + 1;
		int y = snake->seq.back().first;

		CONSOLE::write_at_coord(x, y, '*');

		board[y][x] = '*';
		snake->seq.push({ y, x });
		break;
	}
	case Direction::LEFT:
		break;
	}	
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

void Game::start_game()
{
	this->show_board();

	// init console
	CONSOLE::init();

	// set inital snake position
	this->init_snake();	


	while (true)
	// game loop
	{
		Sleep(_PAUSE_TIME);

		this->move_snake(Direction::RIGHT);
	}
}