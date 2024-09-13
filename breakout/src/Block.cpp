#include "Block.h"
#include "ColorManager.h"
#include "sl.h"
const int rows = 30; //screenHalfHeight / 10;
const int cols = 80; //screenWidth / 10;

static Block blocks[rows][cols];

Block GetBlock(Vector2 offSet);

Block GetBlock(Vector2 offSet)
{
	Block myBlock;
	myBlock.dead = false;
	myBlock.height = 40;
	myBlock.width = myBlock.height;
	myBlock.pos.x = 0;
	myBlock.pos.y = 0;
	myBlock.offSet = offSet;
	return myBlock;
}

void BlockSpace::CreateBlocks()
{
	Vector2 thisOffSet = { 0,screenHeight };

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			blocks[y][x] = GetBlock(thisOffSet);
			blocks[y][x].pos.x = blocks[y][x].offSet.x + blocks[y][x].width / 2;
			blocks[y][x].pos.y = blocks[y][x].offSet.y - blocks[y][x].height / 2;

			thisOffSet.x += blocks[y][x].width;
		}

		thisOffSet.y -= blocks[y][0].height;
	}
}

void BlockSpace::DrawBlocks()
{
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < cols; x++)
		{
			BlockSpace::DrawBlock(blocks[y][x]);
			slCircleFill(blocks[y][x].offSet.x, blocks[y][x].offSet.y, 10.0f, 1000);
		}
}

void BlockSpace::DrawBlock(Block block)
{
	SetForeColor(YELLOW);
	slRectangleFill(block.pos.x, block.pos.y, block.width, block.height);
	SetForeColor(PURPLE);
	slRectangleOutline(block.pos.x, block.pos.y, block.width, block.height);
}