#pragma once
#include "sl.h"
#include "Utils.h"
#include "Rect.h"


struct Ball
{
	int vertices;
	int radius;
	float generalSpeed;
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
	//Draw a ball
	void DrawBall(Ball& ball);
	/// Sets a random angle to the ball and normalizes the speed
	void Normalize360Angle(Ball& ball);
	/// Sets an angle to the ball and normalizes the speed
	void Normalize360Angle(Ball& ball, int angle);
	//Moves the ball and randomizes the angle when it launches.
	void MoveBall(Ball& ball);
	//The ball collides with the edges. 
	void BallEdgeCollision(Ball& ball);
	//Resets the ball to start position.
	void ResetBall(Ball& ball, Rect myRect);
	//Checks if the player pressed the play key
	void CheckPlay(Ball& ball);
}