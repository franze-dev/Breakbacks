#include <iostream>
#include "GameplayScene.h"
#include "Paddle.h"
#include "Ball.h"
#include "KeyManager.h"
#include "math.h"
#include "Block.h"
#include "Player.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "UIManager.h"
#include <string>

namespace GameplayScene
{
	static Paddle mainPaddle;
	static Ball mainBall;
	static Player player;
	static Text lives;
	static Text credits;
	static int textPadding = 20;
	static int defaultFontSize = 30;

	bool CheckWin(Player& player);
	void BallPaddleCollision(Ball& ball, Paddle& square);
	void InitUI();
	void UpdateUI();
	void DrawUI();

	void Init()
	{
		mainPaddle = PaddleSpace::GetDefaultPaddle();
		mainBall = BallSpace::GetDefaultBall();
		BlockSpace::CreateBlocks();
		player = InitDefaultPlayer();
		InitUI();
	}

	void Update()
	{
		if (!BlockSpace::AreBlocksGone() && IsAlive(player))
		{
			UpdateUI();
			PaddleSpace::MovePaddle(mainPaddle);
			BallSpace::CheckPlay(mainBall);
			if (!mainBall.reset)
			{
				BallSpace::MoveBall(mainBall);
			}
			else
				BallSpace::ResetBall(mainBall, mainPaddle);

			BlockSpace::UpdateBlocks(mainBall);
			BallPaddleCollision(mainBall, mainPaddle);
			BallSpace::BallEdgeCollision(mainBall, player);
		}
		else
		{
			if (CheckWin(player))
				player.won = true;
			else
				player.lost = true;

			ResultScene::SavePlayer(player);
			SceneManager::SetCurrentScene(SceneManager::Result);
		}
	}

	void Draw()
	{
		PaddleSpace::DrawPaddle(mainPaddle);
		BallSpace::DrawBall(mainBall);
		BlockSpace::DrawBlocks();
		DrawUI();
	}

	bool CheckWin(Player& player)
	{
		if (!IsAlive(player))
		{
			return false;
		}
		else if (BlockSpace::AreBlocksGone())
		{
			return true;
		}
	}

	void BallPaddleCollision(Ball& ball, Paddle& square)
	{
		int paddleCenterPos = square.pos.x;
		int topOrBottomRand = 0;

		//ANGLES
		//vertical
		int minAngleV = 20;
		int maxAngleV = 360 - minAngleV;
		//horizontal
		int minAngleH = 330;
		int maxAngleH = 340;

		//SQUARE CORNERS		//	c1----------------c3
		Vector2 sCorner1; 		//	|				   |  
		Vector2 sCorner2;		//	|		center	   |  
		Vector2 sCorner3;		//	|				   |  
		Vector2 sCorner4;		//	c2----------------c4  

		//pos x and pos y of square is the center, thanks to sigil.
		sCorner1.x = square.pos.x - square.width / 2;
		sCorner1.y = square.pos.y + square.height / 2;

		sCorner2.x = sCorner1.x;
		sCorner2.y = square.pos.y - square.height / 2;

		sCorner3.x = square.pos.x + square.width / 2;
		sCorner3.y = sCorner1.y;

		sCorner4.x = sCorner3.x;
		sCorner4.y = sCorner2.y;

		Distances calculations;

		calculations.pinPointX = (int)ball.pos.x;
		calculations.pinPointY = (int)ball.pos.y;


		if ((int)ball.pos.x <= (int)sCorner1.x)
			calculations.pinPointX = (int)sCorner1.x; //left

		else if ((int)ball.pos.x >= (int)sCorner3.x)
			calculations.pinPointX = (int)sCorner3.x; //right

		if ((int)ball.pos.y >= (int)sCorner1.y)
			calculations.pinPointY = (int)sCorner1.y; //top

		calculations.distX = (int)ball.pos.x - calculations.pinPointX;
		calculations.distY = (int)ball.pos.y - calculations.pinPointY;
		calculations.distance = sqrt((calculations.distX * calculations.distX) + (calculations.distY * calculations.distY));

		if (calculations.distance <= ball.radius)
		{
			//Is it completely inside the rect? 
			if (ball.pos.y > sCorner2.y &&
				ball.pos.y < sCorner1.y &&
				ball.pos.x < sCorner3.x &&
				ball.pos.x > sCorner1.x)
				ball.pos.y = sCorner1.y + ball.radius * 2;

			//Where does it come from? Is it partially inside the rect?
			//VERTICAL
			if (calculations.pinPointY == (int)sCorner1.y ||
				calculations.pinPointY == (int)sCorner2.y)
			{
				//top
				if (calculations.pinPointY == (int)sCorner1.y)
				{
					ball.pos.y = sCorner1.y + ball.radius * 2;
					BallSpace::Normalize360Angle(ball, GetRandomNum(maxAngleV - minAngleV, minAngleV));

					if (ball.pos.x < paddleCenterPos && ball.speed.x > 0)
						ball.speed.x *= -1;
					else if (ball.pos.x > paddleCenterPos && ball.speed.x < 0)
						ball.speed.x *= -1;

					if (ball.speed.y < 0)
						ball.speed.y *= -1;

				}
			}
			//HORIZONTAL
			else
			{
				//left
				if (calculations.pinPointX == (int)sCorner1.x)
					ball.pos.x = sCorner1.x - ball.radius * 2;
				//right
				else if (calculations.pinPointX == (int)sCorner3.x)
					ball.pos.x = sCorner3.x + ball.radius * 2;

				if ((ball.pos.x == sCorner1.x - ball.radius * 2 && ball.speed.x > 0) ||
					(ball.pos.x == sCorner3.x + ball.radius * 2 && ball.speed.x < 0))
					ball.speed.x *= -1;
			}
		}
	}

	void InitUI()
	{
#pragma region LIVES_TEXT
		lives.content = "LIVES: ";
		lives.currentColor = WHITE;
		lives.fontSize = defaultFontSize;
		lives.location.x = textPadding;
		lives.location.y = screenHeight -lives.fontSize;

#pragma endregion
#pragma region CREDITS_TEXT
		credits.content = "By: S.Alvarez :)";
		credits.currentColor = BLUE;
		credits.fontSize = defaultFontSize / 2;
		credits.location.x = screenWidth - textPadding;
		credits.location.y = screenHeight - credits.fontSize;
#pragma endregion

	}

	void UpdateUI()
	{
		string playerLives = to_string(player.lives);
		lives.content = "LIVES: " + playerLives;
		
	}

	void DrawUI()
	{
		UIManager::PrintText(lives, SL_ALIGN_LEFT);
		UIManager::PrintText(credits, SL_ALIGN_RIGHT);
	}
}

