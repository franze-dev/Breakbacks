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

namespace BlockSpace
{
	void CreateBlocks();
	void DrawBlocks();
	void DrawBlock(Block block);
}
