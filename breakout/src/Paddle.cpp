#include "sl.h"
#include "Paddle.h"
#include "Utils.h"
#include "ColorManager.h"

namespace PaddleSpace
{
	Paddle GetDefaultPaddle()
	{
		Paddle myPaddle;
		myPaddle.width = 200;
		myPaddle.height = 15;
		myPaddle.pos.x = Logic::screenHalfWidth;
		myPaddle.pos.y = 0 + myPaddle.height;
		myPaddle.speed = 500.0f;
		return myPaddle;
	}

	void DrawPaddle(Paddle myPaddle)
	{
		ColorManager::SetForeColor(ColorManager::PURPLE);
		slRectangleFill(myPaddle.pos.x, myPaddle.pos.y, myPaddle.width, myPaddle.height);
	}

	void MovePaddle(Paddle& myPaddle)
	{
		float currentSpeed = myPaddle.speed * slGetDeltaTime();

		int leftKey = SL_KEY_LEFT;
		int rightKey = SL_KEY_RIGHT;

		if (slGetKey(leftKey) && myPaddle.pos.x - myPaddle.width / 2 > 0)
			myPaddle.pos.x -= currentSpeed;
		else if (slGetKey(rightKey) && myPaddle.pos.x + myPaddle.width / 2 < Logic::screenWidth)
			myPaddle.pos.x += currentSpeed;
	}
}

