#pragma once
#include<utility>
#include<queue>


class Snake
{
public:	
	// sequence of coordinates for each snake bit
	std::deque<std::pair<int, int>> seq;

	int get_size();
};

