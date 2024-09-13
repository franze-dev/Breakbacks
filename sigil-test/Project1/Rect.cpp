#include "sl.h"
#include "Paddle.h"
#include "Utils.h"
#include "ColorManager.h"

Paddle PaddleSpace::GetDefaultPaddle()
{
	Paddle myRect;
	myRect.width = 200;
	myRect.height = 15;
	myRect.pos.x = screenHalfWidth;
	myRect.pos.y = 0 + myRect.height;
	myRect.speed = 500.0f;
	return myRect;
}

void PaddleSpace::DrawPaddle(Paddle myRect)
{
	SetForeColor(PURPLE);
	slRectangleFill(myRect.pos.x, myRect.pos.y, myRect.width, myRect.height);
}

void PaddleSpace::MovePaddle(Paddle& myRect)
{
	float currentSpeed = myRect.speed * slGetDeltaTime();

	if (slGetKey(SL_KEY_LEFT) && myRect.pos.x - myRect.width/2 > 0)
		myRect.pos.x -= currentSpeed;
	else if (slGetKey(SL_KEY_RIGHT) && myRect.pos.x + myRect.width / 2 < screenWidth)
		myRect.pos.x += currentSpeed;
}