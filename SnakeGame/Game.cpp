#include <iostream>
#include <Windows.h>
#include "Game.h"
#include "Board.h"

Game::Game(const COORD& cursor_pos, const HANDLE& h_console)
{
	this->cursor_pos = cursor_pos;
	this->h_console  = h_console;

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

	// set tail
	cursor_pos.Y = snake->seq.front().first;
	cursor_pos.X = snake->seq.front().second;
	SetConsoleCursorPosition(h_console, cursor_pos);

	std::cout << "*";

	cursor_pos.Y = snake->seq.back().first;
	cursor_pos.X = snake->seq.back().second;
	SetConsoleCursorPosition(h_console, cursor_pos);

	std::cout << "*";
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

		cursor_pos.X = x;
		cursor_pos.Y = y;

		SetConsoleCursorPosition(h_console, cursor_pos);

		std::cout << "*";
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
	// move tail
	// tail coordinates
	int x = snake->seq.front().second;
	int y = snake->seq.front().first;

	cursor_pos.X = x;
	cursor_pos.Y = y;

	SetConsoleCursorPosition(h_console, cursor_pos);

	std::cout << " ";
	board[y][x] = ' ';
	snake->seq.pop();
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
	this->init_snake();	


	while (true)
	// game loop
	{
		Sleep(50);

		this->move_snake(Direction::RIGHT);
	}
}