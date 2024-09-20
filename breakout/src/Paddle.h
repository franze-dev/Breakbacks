#pragma once
#include "Utils.h"

struct Paddle
{
	Vector2 pos;
	int height;
	int width;
	float speed;
};

namespace PaddleSpace
{
	Paddle GetDefaultPaddle();
	void DrawPaddle(Paddle myPaddle);
	void MovePaddle(Paddle& myPaddle);
};

