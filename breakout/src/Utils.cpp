#include "Utils.h"
#include <iostream>
#include <ctime>

namespace Logic
{
	int GetRandomNum(int max, int add)
	{
		int random = (rand() % max) + add;
		return random;
	}
}

