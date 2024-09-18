#include <iostream>
#include "GameplayScene.h"
#include "Paddle.h"
#include "Ball.h"
#include "KeyManager.h"
#include "math.h"
#include "Block.h"
#include "Player.h"

static Paddle mainRect;
static Ball mainBall;
static Player player;

void BallRectCollision(Ball& ball, Paddle& square);

void GameplayScene::Init()
{
	mainRect = PaddleSpace::GetDefaultPaddle();
	mainBall = BallSpace::GetDefaultBall();
	BlockSpace::CreateBlocks();
}

void GameplayScene::Update()
{
	/*if (!BlockSpace::AreBlocksGone() && IsAlive(player))
	{*/
		PaddleSpace::MovePaddle(mainRect);
		BallSpace::CheckPlay(mainBall);
		if (!mainBall.reset)
		{
			BallSpace::MoveBall(mainBall);
		}
		else
			BallSpace::ResetBall(mainBall, mainRect);

		BlockSpace::UpdateBlocks(mainBall);
		BallRectCollision(mainBall, mainRect);
		BallSpace::BallEdgeCollision(mainBall, player);
	//}
	
}

void GameplayScene::Draw()
{
	PaddleSpace::DrawPaddle(mainRect);
	BallSpace::DrawBall(mainBall);
	BlockSpace::DrawBlocks();
}

void BallRectCollision(Ball& ball, Paddle& square)
{
	int rectCenterPos = square.pos.x;
	int topOrBottomRand = 0;

	//ANGLES
	//vertical
	int minAngleV = 50;
	int maxAngleV = 80;
	//horizontal
	int minAngleH = 330;
	int maxAngleH = 340;

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

	calculations.distX = (int)ball.pos.x - calculations.pinPointX;
	calculations.distY = (int)ball.pos.y - calculations.pinPointY;
	calculations.distance = sqrt((calculations.distX * calculations.distX) + (calculations.distY * calculations.distY));

	if (calculations.distance <= ball.radius)
	{
		//Is it completely inside the rect? 
		if (ball.pos.y > sCorner2.y &&
			ball.pos.y < sCorner1.y &&
			ball.pos.x < sCorner3.x &&
			ball.pos.x > sCorner1.x)
			ball.pos.y = sCorner1.y + ball.radius * 2;

		//Where does it come from? Is it partially inside the rect?
		//VERTICAL
		if (calculations.pinPointY == (int)sCorner1.y ||
			calculations.pinPointY == (int)sCorner2.y)
		{
			//top
			if (calculations.pinPointY == (int)sCorner1.y)
			{
				ball.pos.y = sCorner1.y + ball.radius * 2;
				BallSpace::Normalize360Angle(ball, GetRandomNum(maxAngleV - minAngleV, minAngleV));

				if (ball.pos.x < rectCenterPos && ball.speed.x > 0)
					ball.speed.x *= -1;
				else if (ball.pos.x > rectCenterPos && ball.speed.x < 0)
					ball.speed.x *= -1;

				if (ball.speed.y < 0)
					ball.speed.y *= -1;

			}
		}
		//HORIZONTAL
		else
		{
			//left
			if (calculations.pinPointX == (int)sCorner1.x)
				ball.pos.x = sCorner1.x - ball.radius * 2;
			//right
			else if (calculations.pinPointX == (int)sCorner3.x)
				ball.pos.x = sCorner3.x + ball.radius * 2;

			if ((ball.pos.x == sCorner1.x - ball.radius * 2 && ball.speed.x > 0) || 
				(ball.pos.x == sCorner3.x + ball.radius * 2 && ball.speed.x < 0 ))
				ball.speed.x *= -1;
		}
	}
}