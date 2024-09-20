#include "sl.h"
#include "Paddle.h"
#include "Utils.h"
#include "ColorManager.h"



Paddle PaddleSpace::GetDefaultPaddle()
{
	Paddle myPaddle;
	myPaddle.width = 200;
	myPaddle.height = 15;
	myPaddle.pos.x = screenHalfWidth;
	myPaddle.pos.y = 0 + myPaddle.height;
	myPaddle.speed = 500.0f;
	return myPaddle;
}

void PaddleSpace::DrawPaddle(Paddle myPaddle)
{
	SetForeColor(PURPLE);
	slRectangleFill(myPaddle.pos.x, myPaddle.pos.y, myPaddle.width, myPaddle.height);
}

void PaddleSpace::MovePaddle(Paddle& myPaddle)
{
	float currentSpeed = myPaddle.speed * slGetDeltaTime();

	int leftKey = 'A';
	int rightKey = 'D';

	if (slGetKey(leftKey) && myPaddle.pos.x - myPaddle.width/2 > 0)
		myPaddle.pos.x -= currentSpeed;
	else if (slGetKey(rightKey) && myPaddle.pos.x + myPaddle.width / 2 < screenWidth)
		myPaddle.pos.x += currentSpeed;
}