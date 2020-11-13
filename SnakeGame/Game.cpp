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
	snake->tail = { 2,2 };
	snake->head = { 2,3 };

	cursor_pos.Y = snake->tail.first;
	cursor_pos.X = snake->tail.second;

	SetConsoleCursorPosition(console, cursor_pos);

	std::cout << "*";

	cursor_pos.Y = snake->head.first;
	cursor_pos.X = snake->head.second;

	SetConsoleCursorPosition(console, cursor_pos);

	std::cout << "*";
}

void Game::move_snake(COORD& cursor_pos, const HANDLE& console /* Directions */)
{
	// TODO: hide cursor

	// move tail
	cursor_pos.Y = snake->tail.first;
	cursor_pos.X = snake->tail.second;

	SetConsoleCursorPosition(console, cursor_pos);

	std::cout << " ";
	snake->tail.second++;

	// move head
	cursor_pos.Y = snake->head.first;
	cursor_pos.X = ++snake->head.second;

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
	{
		Sleep(1000);

		this->move_snake(cursor_pos, console /* Direction */);
	}
}