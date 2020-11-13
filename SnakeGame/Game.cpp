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

void Game::start_game()
{	
	// test
	snake->head = { 1,2 };
	snake->tail = { 1,1 };

	board[snake->tail.first][snake->tail.second] = '*';
	board[snake->head.first][snake->head.second] = '*';	

	this->show_board();

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) return;

	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	GetConsoleScreenBufferInfo(console, &csbi);
	COORD coordCur = csbi.dwCursorPosition;

	while (true)
	{
		Sleep(1000);
		
		// TODO: hide cursor
		coordCur.Y = snake->tail.first;
		coordCur.X = snake->tail.second;		

		// board[snake->tail.first][snake->tail.second] = ' ';
		// board[snake->head.first][snake->head.second + 1] = '*';

		SetConsoleCursorPosition(console, coordCur);

		std::cout << " ";

		// move head
		coordCur.Y = snake->head.first;
		coordCur.X = ++snake->head.second;

		SetConsoleCursorPosition(console, coordCur);

		std::cout << "*";

		snake->tail.second++;	
	}
}