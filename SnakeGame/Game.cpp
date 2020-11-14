#include <iostream>
#include <Windows.h>
#include "Game.h"
#include "Board.h"

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

void Game::init_snake(COORD& cursor_pos, const HANDLE& console)
{
	snake->seq.push({ 2,2 }); // front
	snake->seq.push({ 2,3 }); // back

	// set tail
	cursor_pos.Y = snake->seq.front().first;
	cursor_pos.X = snake->seq.front().second;
	SetConsoleCursorPosition(console, cursor_pos);

	std::cout << "*";

	cursor_pos.Y = snake->seq.back().first;
	cursor_pos.X = snake->seq.back().second;
	SetConsoleCursorPosition(console, cursor_pos);

	std::cout << "*";
}

void Game::move_snake(COORD& cursor_pos, const HANDLE& console, Direction dir)
{
	// TODO: hide cursor

	// move tail
	// tail coordinates
	int x_tail = snake->seq.front().second;
	int y_tail = snake->seq.front().first;

	cursor_pos.X = x_tail;
	cursor_pos.Y = y_tail;

	SetConsoleCursorPosition(console, cursor_pos);

	std::cout << " ";
	snake->seq.pop();

	switch (dir)
	{
	case Direction::UP:
		break;
	case Direction::DOWN:
		break;
	case Direction::RIGHT:
		break;
	case Direction::LEFT:
		break;
	}
	
	// move head

	int x_head = snake->seq.back().second;
	int y_head = snake->seq.back().first;

	SetConsoleCursorPosition(console, cursor_pos);

	std::cout << "*";
}

void Game::start_game()
{
	this->show_board();

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) return;

	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	GetConsoleScreenBufferInfo(console, &csbi);
	COORD cursor_pos = csbi.dwCursorPosition;

	// set inital snake position
	this->init_snake(cursor_pos, console);	


	while (true)
	// game loop
	{
		Sleep(500);

		this->move_snake(cursor_pos, console, Direction::RIGHT);
	}
}