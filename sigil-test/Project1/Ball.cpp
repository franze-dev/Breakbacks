#include "Ball.h"
#include "ColorManager.h"
#include <iostream>
#include <ctime>

Ball BallSpace::GetDefaultBall()
{
	Ball ball;

	ball.vertices = 1000;
	ball.radius = 10;
	ball.generalSpeed = 600.0f;
	ball.pos = { (float)screenHalfWidth + ball.radius, (float)screenHalfHeight + ball.radius };
	ball.speed = { ball.generalSpeed, ball.generalSpeed };
	ball.defaultSpeed = ball.speed;
	ball.reset = true;
	ball.randomizeDirection = false;

	return ball;
}

void BallSpace::DrawBall(Ball& ball)
{
	SetForeColor(WHITE);
	slCircleFill(ball.pos.x, ball.pos.y, ball.radius, ball.vertices);
}

void BallSpace::Normalize360Angle(Ball& ball)
{
	int angle = 0;
	int magnitude = 0;
	Vector2 direction;

	angle = GetRandomNum(360, 0);

	//To make sure the speed is not zero or a number I cannot work with, I set it to default to be safe.
	ball.speed = ball.defaultSpeed;

	//I calculate the directions the ball will go to (depending on the angles)
	direction.x = cos(angle);
	direction.y = sin(angle);

	//The magnitude helps me normalize it so when it multiplies with the speed, the speed itself will not be too visibly modified in the game.
	magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude > 0)
	{
		direction.x /= magnitude;
		direction.y /= magnitude;
	}

	ball.speed.y *= direction.y;
	ball.speed.x *= direction.x;
}

void BallSpace::Normalize360Angle(Ball& ball, int angle)
{
	//Explained this in the other version of the function.

	std::cout << angle << std::endl;

	int magnitude = 0;
	Vector2 direction;

	ball.speed = ball.defaultSpeed;

	direction.x = cos(angle);

	direction.y = sin(angle);

	magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude > 0)
	{
		direction.x /= magnitude;
		direction.y /= magnitude;
	}

	ball.speed.y *= direction.y;
	ball.speed.x *= direction.x;
}

void BallSpace::MoveBall(Ball& ball)
{
	int minAngle = 30;
	int maxAngle = 100;

	if (ball.randomizeDirection)
	{
		BallSpace::Normalize360Angle(ball, GetRandomNum(maxAngle-minAngle, minAngle));
		if (ball.speed.y < 0)
			ball.speed.y *= -1;

		ball.randomizeDirection = false;
	}

	ball.pos.x += ball.speed.x * slGetDeltaTime();
	ball.pos.y += ball.speed.y * slGetDeltaTime();
}

void BallSpace::BallEdgeCollision(Ball& ball)
{
	int angle = 0;
	int magnitude = 0;
	Vector2 direction;

	//I made a range in which the ball could go a bit too slow / make an infinite bounce from the top and bottom of the screen.
	int centerRange1 = screenHalfWidth - 50;
	int centerRange2 = screenHalfWidth + 50;

	//This is so it detects if the ball is going a bit too slow in that range
	float minimumPosSpeed = ball.generalSpeed / 3;
	float minimumNegSpeed = minimumPosSpeed * -1;

	//sides
	if ((ball.pos.x >= (screenWidth - ball.radius)) || (ball.pos.x <= ball.radius))
	{
		//When a player scores a point, the ball goes back to the center.
		if ((int)ball.pos.x >= (screenWidth - ball.radius))
			ball.pos.x = screenWidth - ball.radius;
		else
			ball.pos.x = ball.radius;

		ball.speed.x *= -1.0f;

	}

	//top / bottom
	if ((ball.pos.y >= (screenHeight - ball.radius)) || (ball.pos.y <= ball.radius))
	{
		//Teleports the ball inside the wall bounds to prevent it from glitching outside of the screen.
		if ((int)ball.pos.y >= (screenHeight - ball.radius))
		{
			ball.pos.y = screenHeight - ball.radius;
			ball.speed.y *= -1.0f;
		}
		else
		{
			ball.reset = true;

		}

		

	}
}

void BallSpace::ResetBall(Ball& ball, Rect myRect)
{
	ball.pos.x = myRect.pos.x;
	ball.pos.y = myRect.pos.y + ball.radius*2;
	ball.reset = true;
	ball.randomizeDirection = true;
}

void BallSpace::CheckPlay(Ball& ball)
{
	if (slGetKey(' '))
		ball.reset = false;
}
