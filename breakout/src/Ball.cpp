#include "Ball.h"
#include "ColorManager.h"
#include <iostream>
#include <ctime>
#include "Player.h"

const int ballMaxAngle = 360;
const int ballMinAngle = 20;

namespace BallSpace
{
	void ResetSpeed(Ball& ball);

	void ResetSpeed(Ball& ball)
	{
		ball.speed = ball.defaultSpeed;
		ball.generalSpeed = ball.defaultSpeed.x;
	}

	Ball GetDefaultBall()
	{
		Ball ball;

		ball.vertices = 1000;
		ball.radius = 10;
		ball.defaultRadius = ball.radius;
		ball.plusRadius = ball.radius * 3;
		ball.generalSpeed = 350.0f;
		ball.increasePercentage = 100.0f;
		ball.speedIncrease = ball.generalSpeed * ball.increasePercentage / 100;
		ball.pos = { (float)screenHalfWidth + ball.radius, (float)screenHalfHeight + ball.radius };
		ball.speed = { ball.generalSpeed, ball.generalSpeed };
		ball.defaultSpeed = ball.speed;
		ball.reset = true;
		ball.randomizeDirection = false;
		ball.spedUp = false;
		ball.color = WHITE;
		ball.currentPower = PowerUps::None;

		return ball;
	}

	void IncreaseSpeed(Ball& ball)
	{
		if (ball.speed.x > 0)
			ball.speed.x += ball.increasePercentage;
		else
			ball.speed.x -= ball.increasePercentage;

		if (ball.speed.y > 0)
			ball.speed.y += ball.increasePercentage;
		else
			ball.speed.y -= ball.increasePercentage;

		if (ball.generalSpeed > 0)
			ball.generalSpeed += ball.increasePercentage;
		else
			ball.generalSpeed -= ball.increasePercentage;

	}

	void IncreaseSize(Ball& ball)
	{
		ball.radius = ball.plusRadius;
	}

	void DrawBall(Ball ball)
	{
		SetForeColor(ball.color);
		slCircleFill(ball.pos.x, ball.pos.y, ball.radius, ball.vertices);
	}

	void Normalize360Angle(Ball& ball)
	{
		int angle = 0;
		int magnitude = 0;
		Vector2 direction;

		angle = GetRandomNum(360, 0);

		//To make sure the speed is not zero or a number I cannot work with, I set it to default to be safe.
		ball.speed.y = ball.generalSpeed;
		ball.speed.x = ball.generalSpeed;

		//I calculate the directions the ball will go to (depending on the angles)
		direction.x = sin(angle);
		direction.y = -cos(angle);

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

	void Normalize360Angle(Ball& ball, int angle)
	{
		//Explained this in the other version of the function.

		int magnitude = 0;
		Vector2 direction;

		ball.speed.x = ball.generalSpeed;
		ball.speed.y = ball.generalSpeed;

		direction.x = sin(angle);

		direction.y = -cos(angle);

		magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

		if (magnitude > 0)
		{
			direction.x /= magnitude;
			direction.y /= magnitude;
		}

		ball.speed.y *= direction.y;
		ball.speed.x *= direction.x;
	}

	void MoveBall(Ball& ball)
	{
		int maxAngle = ballMaxAngle - ballMinAngle;

		if (ball.randomizeDirection)
		{
			Normalize360Angle(ball, GetRandomNum(maxAngle - ballMinAngle, ballMinAngle));
			if (ball.speed.y < 0)
				ball.speed.y *= -1;

			ball.randomizeDirection = false;
		}

		ball.pos.x += ball.speed.x * slGetDeltaTime();
		ball.pos.y += ball.speed.y * slGetDeltaTime();
	}

	void BallEdgeCollision(Ball& ball, Player& player)
	{
		Vector2 previousSpeed;


		//This is so it detects if the ball is going a bit too slow in that range
		float minimumPosSpeed = ball.generalSpeed / 3;
		float minimumNegSpeed = minimumPosSpeed * -1.0f;

		// sides
		if ((ball.pos.x >= (screenWidth - ball.radius)) || (ball.pos.x <= ball.radius))
		{
			if ((int)ball.pos.x >= (screenWidth - ball.radius))
				ball.pos.x = screenWidth - ball.radius;
			else
				ball.pos.x = ball.radius;

			//Also verifies if the ball is "slow". 
			//If the speed in y is too low, I'll make it a bit faster for the sake of dynamic gameplay.
			if ((ball.speed.y < minimumPosSpeed && ball.speed.y > 0) ||
				ball.speed.y > minimumNegSpeed && ball.speed.y < 0)
			{
				previousSpeed = ball.speed;
				
				//Here's a problem. I want to make it random, but it's not accurate. Because it can try to go
				//downwards when it's at the bottom, or to the left when it's supposed to go to the right.
				//All of these problems are covered bellow.
				BallSpace::Normalize360Angle(ball);

				if (ball.pos.x > screenWidth / 2 && ball.speed.x < 0)
				{
					//turns RIGHT
					ball.speed.x *= -1;
				}
				else if (ball.pos.x < screenWidth / 2 && ball.speed.x > 0)
				{
					//turns LEFT
					ball.speed.x *= -1;
				}

				if (previousSpeed.y > 0 && ball.speed.y < 0)
				{
					//goes UP
					ball.speed.y *= -1;

				}
				else if (previousSpeed.y < 0 && ball.speed.y > 0)
				{
					//goes DOWN
					ball.speed.y *= -1;
				}
			}
			else
				ball.speed.x *= -1.0f;

		}

		// top / bottom
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
				if (IsAlive(player))
					LooseLife(player);
				ball.reset = true;
			}
		}
	}

	void ResetBall(Ball& ball, Paddle myRect)
	{
		ball.pos.x = myRect.pos.x;
		ball.pos.y = myRect.pos.y + ball.radius * 2;
		ball.reset = true;
		ball.randomizeDirection = true;
		ball.color = WHITE;
		ResetSpeed(ball);
		if (ball.currentPower != PowerUps::None)
			SetPower(PowerUps::None, ball);
	}

	void CheckPlay(Ball& ball)
	{
		if (slGetKey(' '))
			ball.reset = false;
	}

	void SetPower(PowerUps power, Ball& ball)
	{
		switch (power)
		{
		case PowerUps::None:
			ball.currentPower = PowerUps::None;
			ball.color = WHITE;
			std::cout << "NO POWER" << std::endl;
			break;
		case PowerUps::Speed:
			ball.currentPower = PowerUps::Speed;
			ball.color = YELLOW;
			std::cout << "SPEED" << std::endl;
			break;
		case PowerUps::PlusSize:
			ball.currentPower = PowerUps::PlusSize;
			ball.color = RED;
			std::cout << "SIZE" << std::endl;
			break;
		case PowerUps::NoBounce:
			ball.color = BLUE;
			ball.currentPower = PowerUps::NoBounce;
			std::cout << "NO-BOUNCE" << std::endl;
			break;
		default:
			ball.currentPower = PowerUps::None;
			ball.color = WHITE;
			std::cout << "NO POWER" << std::endl;
			break;
		}

		if (ball.spedUp && ball.currentPower != PowerUps::Speed)
		{
			ball.spedUp = false;
			ResetSpeed(ball);
		}

		if (ball.radius == ball.plusRadius && ball.currentPower != PowerUps::PlusSize)
			ball.radius = ball.defaultRadius;
	}
}

