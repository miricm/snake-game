#pragma once
#include<utility>

class Snake
{
public:
	int size;

	// coordinates of snakes head and tail
	std::pair<int, int> head;
	std::pair<int, int> tail;
};

