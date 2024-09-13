#pragma once
#include "Utils.h"


struct Block
{
	Vector2 offSet; //refers to a corner
	Vector2 pos;
	int height;
	int width;
	bool dead;
};

void CreateBlocks();