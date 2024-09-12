#include "Utils.h"
#include <iostream>
#include <ctime>

int GetRandomNum(int max, int add)
{
	int random = (rand() % max) + add;
	return random;
}