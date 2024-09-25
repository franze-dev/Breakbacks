#pragma once
#include "Utils.h"

namespace PaddleSpace
{
	struct Paddle
	{
		Logic::Vector2 pos;
		int height;
		int width;
		float speed;
	};

	Paddle GetDefaultPaddle();
	void DrawPaddle(Paddle myPaddle);
	void MovePaddle(Paddle& myPaddle);
};

