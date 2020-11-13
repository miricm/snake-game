#include "Board.h"

char** Board::create_board()
{
	char** board = new char*[Board::HEIGHT];

	for (size_t i = 0; i < Board::HEIGHT; i++)
	{
		board[i] = new char[Board::WIDTH];
		for (size_t j = 0; j < Board::WIDTH; j++)
		{
			if (i == 0 || i == Board::HEIGHT - 1 
				|| j == 0 || j == Board::WIDTH - 1)
			{
				board[i][j] = '#';
			}
			else board[i][j] = ' ';
		}
	}

	return board;
}
