#include "Block.h"
#include "sl.h"
const int rows = 30; //screenHalfHeight / 10;
const int cols = 80; //screenWidth / 10;

static Block blocks[rows][cols];

Block GetBlock(Vector2 offSet)
{
	Block myBlock;
	myBlock.dead = false;
	myBlock.height = 10;
	myBlock.width = myBlock.width;
	myBlock.pos.x = 0;
	myBlock.pos.y = 0;
	myBlock.offSet = offSet;
	return myBlock;
}

void CreateBlocks()
{
	Vector2 thisOffSet = { 0,0 };

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			blocks[y][x] = GetBlock(thisOffSet);
			blocks[y][x].pos.x = blocks[y][x].offSet.x + blocks[y][x].width / 2;
			blocks[y][x].pos.y = blocks[y][x].offSet.y - blocks[y][x].height / 2;

			thisOffSet.x += blocks[y][x].width;
		}
		thisOffSet.y += blocks[y][0].height;
	}
}

void DrawBlocks()
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			DrawBlock(blocks[y][x]);
		}
	}
}

void DrawBlock(Block block)
{
	slRectangleFill(block.pos.x, block.pos.y, block.width, block.height);
}