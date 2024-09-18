#pragma once
#include "sl.h"
#include "Utils.h"
#include "Paddle.h"
#include "Player.h"

//To calculate the distance between the ball and a square (block or rect)
struct Distances
{
	int pinPointX;
	int pinPointY;
	int distX;
	int distY;
	int distance;
};

struct Ball
{
	int vertices;
	int radius;
	float generalSpeed;
	float increasePercentage;
	float speedIncrease;
	Vector2 pos;
	Vector2 speed;
	Vector2 defaultSpeed;
	bool reset;
	bool randomizeDirection;
};

namespace BallSpace
{
	//Initializes a ball
	Ball GetDefaultBall();
	//increases the speed to a percentage
	void IncreaseSpeed(Ball& ball);
	//Draw a ball
	void DrawBall(Ball& ball);
	/// Sets a random angle to the ball and normalizes the speed
	void Normalize360Angle(Ball& ball);
	/// Sets an angle to the ball and normalizes the speed
	void Normalize360Angle(Ball& ball, int angle);
	//Moves the ball and randomizes the angle when it launches.
	void MoveBall(Ball& ball);
	//The ball collides with the edges. 
	void BallEdgeCollision(Ball& ball, Player& player);
	//Resets the ball to start position.
	void ResetBall(Ball& ball, Paddle myRect);
	//Checks if the player pressed the play key
	void CheckPlay(Ball& ball);
}