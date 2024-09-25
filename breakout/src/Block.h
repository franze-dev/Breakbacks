#pragma once
#include "Utils.h"
#include "Ball.h"
#include "ColorManager.h"

namespace BlockSpace
{
	struct Block
	{
		Logic::Vector2 offSet; //refers to a corner
		Logic::Vector2 pos;
		int height;
		int width;
		//int lives;
		bool dead;
	};

	bool AreBlocksGone();
	void CreateBlocks();
	void UpdateBlocks(BallSpace::Ball& ball);
	void DrawBlocks();
	void DrawBlock(Block block);
}
