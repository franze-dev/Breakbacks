#include "Block.h"
#include "ColorManager.h"
#include <iostream>
#include "sl.h"
#include <math.h>
const int rows = 5;
const int cols = 20;

static Block blocks[rows][cols];

Block GetBlock(Vector2 offSet);
void BlockBallCollision(Ball& ball, Block& square);

Block GetBlock(Vector2 offSet)
{
	Block myBlock;
	myBlock.height = 40;
	myBlock.width = myBlock.height;
	myBlock.pos.x = 0;
	myBlock.pos.y = 0;
	myBlock.offSet = offSet;
	myBlock.dead = false;
	return myBlock;
}

void BlockBallCollision(Ball& ball, Block& square)
{
	int blockCenterPos = square.pos.x;

	//SQUARE CORNERS		//	c1----------------c3
	Vector2 sCorner1; 		//	|				   |  
	Vector2 sCorner2;		//	|		center	   |  
	Vector2 sCorner3;		//	|				   |  
	Vector2 sCorner4;		//	c2----------------c4  

	//pos x and pos y of square is the center, thanks to sigil.
	sCorner1.x = square.pos.x - square.width / 2;
	sCorner1.y = square.pos.y + square.height / 2;

	sCorner2.x = sCorner1.x;
	sCorner2.y = square.pos.y - square.height / 2;

	sCorner3.x = square.pos.x + square.width / 2;
	sCorner3.y = sCorner1.y;

	sCorner4.x = sCorner3.x;
	sCorner4.y = sCorner2.y;

	Distances calculations;

	calculations.pinPointX = (int)ball.pos.x;
	calculations.pinPointY = (int)ball.pos.y;


	if ((int)ball.pos.x <= (int)sCorner1.x)
		calculations.pinPointX = (int)sCorner1.x; //left

	else if ((int)ball.pos.x >= (int)sCorner3.x)
		calculations.pinPointX = (int)sCorner3.x; //right

	if ((int)ball.pos.y >= (int)sCorner1.y)
		calculations.pinPointY = (int)sCorner1.y; //top

	else if ((int)ball.pos.y <= (int)sCorner2.y)
		calculations.pinPointY = (int)sCorner2.y; //bottom

	calculations.distX = (int)ball.pos.x - calculations.pinPointX;
	calculations.distY = (int)ball.pos.y - calculations.pinPointY;
	calculations.distance = sqrt((calculations.distX * calculations.distX) + (calculations.distY * calculations.distY));

	if (calculations.distance < ball.radius)
	{

		//Where does it come from? Is it partially inside the rect?
		//VERTICAL
		if (calculations.pinPointY == (int)sCorner1.y ||
			calculations.pinPointY == (int)sCorner2.y)
		{
			//top
			if (calculations.pinPointY == (int)sCorner1.y)
			{
				ball.pos.y = sCorner1.y + ball.radius * 2;

				/*if (ball.speed.y < 0)
				{*/
					ball.speed.y *= -1;
				//}
			}

			//bottom
			if (calculations.pinPointY == (int)sCorner2.y)
			{
				ball.pos.y = sCorner2.y - ball.radius * 2;

				/*if (ball.speed.y > 0)
				{*/
					ball.speed.y *= -1;
				//}
			}
		}
		//HORIZONTAL
		else if(calculations.pinPointX == (int)sCorner1.x ||
				calculations.pinPointX == (int)sCorner3.x)
		{
			//left
			if (calculations.pinPointX == (int)sCorner1.x)
				ball.pos.x = sCorner1.x - ball.radius * 2;
			//right
			else if (calculations.pinPointX == (int)sCorner3.x)
				ball.pos.x = sCorner3.x + ball.radius * 2;

			/*if ((ball.pos.x == sCorner1.x - ball.radius * 2 && ball.speed.x > 0) ||
				(ball.pos.x == sCorner3.x + ball.radius * 2 && ball.speed.x < 0))*/
				ball.speed.x *= -1;
		}

		//Is it completely inside the rect? 
		if (ball.pos.y > sCorner2.y &&
			ball.pos.y < sCorner1.y &&
			ball.pos.x < sCorner3.x &&
			ball.pos.x > sCorner1.x)
			ball.pos.y = sCorner2.y - ball.radius * 2;

		square.dead = true;
		BallSpace::IncreaseSpeed(ball);
	}
}

void BlockSpace::CreateBlocks()
{
	int offSetX = 0;
	int offSetY = screenHeight * 4 / 5;
	Vector2 thisOffSet = { offSetX,offSetY };

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
		thisOffSet.x = 0;
	}
}

void BlockSpace::UpdateBlocks(Ball& ball)
{
	for (int y = rows - 1; y >= 0; y--)
		for (int x = 0; x < cols; x++)
			if (!blocks[y][x].dead)
				BlockBallCollision(ball, blocks[y][x]);

}

void BlockSpace::DrawBlocks()
{
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < cols; x++)
			if (!blocks[y][x].dead)
				BlockSpace::DrawBlock(blocks[y][x]);
}

void BlockSpace::DrawBlock(Block block)
{
	SetForeColor(GREEN);
	slRectangleFill(block.pos.x, block.pos.y, block.width, block.height);
	SetForeColor(PURPLE);
	slRectangleOutline(block.pos.x, block.pos.y, block.width, block.height);
}

