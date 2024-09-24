#pragma once
#include "sl.h"
#include "Utils.h"
#include "Paddle.h"
#include "Player.h"
#include "ColorManager.h"

//To calculate the distance between the ball and a square (block or paddle)
struct Distances
{
	int pinPointX;
	int pinPointY;
	int distX;
	int distY;
	int distance;
};

enum class PowerUps
{
	None,

	//The ball can break up to 5 blocks until it loses the power.

	//increases speed by 10% without warning 
	Speed,
	//bigger ball, bigger collision
	PlusSize,
	//the ball doesn't bounce off of the blocks, it just breaks through them. 
	NoBounce
};

struct Ball
{
	int vertices;
	int radius;
	int defaultRadius;
	int plusRadius;
	float generalSpeed;
	float increasePercentage;
	float speedIncrease;
	Vector2 pos;
	Vector2 speed;
	Vector2 defaultSpeed;
	bool reset;
	bool randomizeDirection;
	bool spedUp;
	Colors color;
	PowerUps currentPower;
};



namespace BallSpace
{
	//Initializes a ball
	Ball GetDefaultBall();
	//increases the speed to a percentage
	void IncreaseSpeed(Ball& ball);
	//Increases the ball size
	void IncreaseSize(Ball& ball);
	//Draw a ball
	void DrawBall(Ball ball);
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
	//Sets a power up to the ball or resets it
	void SetPower(PowerUps power, Ball& ball);
}