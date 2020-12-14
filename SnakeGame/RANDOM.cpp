#include<iostream>

#include "RANDOM.h"

static bool first_time_seeding = true;

int RANDOM::get(int min, int max)
{
	if (first_time_seeding)
	{
		srand(time(NULL));
		first_time_seeding = false;
	}

	return min + rand() % ((max + 1) - min);
}