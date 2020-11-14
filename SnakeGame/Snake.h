#pragma once
#include<utility>
#include<queue>


class Snake
{
public:	
	// sequence of coordinates for each snake bit
	std::queue<std::pair<int, int>> seq;

	int get_size();
};

