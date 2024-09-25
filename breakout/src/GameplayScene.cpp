#include <iostream>
#include "GameplayScene.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Player.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "UIManager.h"
#include "PauseMenu.h"

#include <string>


namespace GameplayScene
{
	static PaddleSpace::Paddle mainPaddle;
	static BallSpace::Ball mainBall;
	static PlayerSpace::Player player;
	static UIManager::Text livesText;
	static UIManager::Text creditsText;
	static UIManager::Text pauseText;
	static UIManager::Text powerUpText;
	static int textPadding = 20;
	static int defaultFontSize = 30;

	static bool paused = false;

	void CheckPause();
	bool CheckWin(PlayerSpace::Player& player);
	void BallPaddleCollision(BallSpace::Ball& ball, PaddleSpace::Paddle& square);
	void InitUI();
	void UpdateUI();
	void DrawUI();

	void Init()
	{
		paused = false;
		mainPaddle = PaddleSpace::GetDefaultPaddle();
		mainBall = BallSpace::GetDefaultBall();
		BlockSpace::CreateBlocks();
		player = PlayerSpace::InitDefaultPlayer();
		InitUI();
		PauseMenu::Init();
	}

	void Update()
	{
		if (!BlockSpace::AreBlocksGone() && IsAlive(player))
		{
			if (!paused)
			{
				if (!mainBall.spedUp && mainBall.currentPower == BallSpace::PowerUps::Speed)
				{
					BallSpace::IncreaseSpeed(mainBall);
					mainBall.spedUp = true;
				}

				if (mainBall.radius != mainBall.plusRadius && mainBall.currentPower == BallSpace::PowerUps::PlusSize)
					BallSpace::IncreaseSize(mainBall);

				CheckPause();
				UpdateUI();
				PaddleSpace::MovePaddle(mainPaddle);
				BallSpace::CheckPlay(mainBall);
				if (!mainBall.reset)
					BallSpace::MoveBall(mainBall);
				else
					BallSpace::ResetBall(mainBall, mainPaddle);

				BlockSpace::UpdateBlocks(mainBall);
				BallPaddleCollision(mainBall, mainPaddle);
				BallSpace::BallEdgeCollision(mainBall, player);
			}
			else
				PauseMenu::Update();
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
		if (paused)
			PauseMenu::Draw();
	}

	void CheckPause()
	{
		if (slGetKey('P'))
			paused = true;
	}

	bool CheckWin(PlayerSpace::Player& player)
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

	void BallPaddleCollision(BallSpace::Ball& ball, PaddleSpace::Paddle& square)
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

		//SQUARE CORNERS				//	c1----------------c3
		Logic::Vector2 sCorner1; 		//	|				   |  
		Logic::Vector2 sCorner2;		//	|		center	   |  
		Logic::Vector2 sCorner3;		//	|				   |  
		Logic::Vector2 sCorner4;		//	c2----------------c4  

		//pos x and pos y of square is the center, thanks to sigil.
		sCorner1.x = square.pos.x - square.width / 2;
		sCorner1.y = square.pos.y + square.height / 2;

		sCorner2.x = sCorner1.x;
		sCorner2.y = square.pos.y - square.height / 2;

		sCorner3.x = square.pos.x + square.width / 2;
		sCorner3.y = sCorner1.y;

		sCorner4.x = sCorner3.x;
		sCorner4.y = sCorner2.y;

		BallSpace::Distances calculations;

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
					BallSpace::Normalize360Angle(ball, Logic::GetRandomNum(maxAngleV - minAngleV, minAngleV));

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
		livesText = UIManager::GetText(textPadding, Logic::screenHeight - defaultFontSize, defaultFontSize, "LIVES: ", ColorManager::WHITE);
		creditsText = UIManager::GetText(Logic::screenWidth - textPadding, Logic::screenHeight - defaultFontSize / 2, defaultFontSize / 2, "By: S.Alvarez :)", ColorManager::BLUE);
		pauseText = UIManager::GetText(Logic::screenWidth - textPadding, defaultFontSize, defaultFontSize / 2, "Press 'P' to pause", ColorManager::PURPLE);
		powerUpText = UIManager::GetText(textPadding, defaultFontSize, defaultFontSize / 2, "NO ACTIVE POWER UP!", ColorManager::WHITE);

	}

	void UpdateUI()
	{
		string playerLives = to_string(player.lives);
		livesText.content = "LIVES: " + playerLives;

		switch (mainBall.currentPower)
		{
		case BallSpace::PowerUps::None:
			powerUpText.content = "NO ACTIVE POWER UP!";
			powerUpText.currentColor = ColorManager::WHITE;
			break;
		case BallSpace::PowerUps::NoBounce:
			powerUpText.content = "CLEAR THE SCREEN!";
			powerUpText.currentColor = ColorManager::BLUE;
			break;
		case BallSpace::PowerUps::Speed:
			powerUpText.content = "SPEED OF LIGHT!";
			powerUpText.currentColor = ColorManager::YELLOW;
			break;
		case BallSpace::PowerUps::PlusSize:
			powerUpText.content = "THINK BIG!";
			powerUpText.currentColor = ColorManager::RED;
			break;

		default:
			break;
		}

	}

	void DrawUI()
	{
		UIManager::PrintText(livesText, SL_ALIGN_LEFT);
		UIManager::PrintText(creditsText, SL_ALIGN_RIGHT);
		UIManager::PrintText(pauseText, SL_ALIGN_RIGHT);
		UIManager::PrintText(powerUpText, SL_ALIGN_LEFT);
	}

	void PauseGame()
	{
		if (!paused)
			paused = true;
	}

	void UnPauseGame()
	{
		if (paused)
			paused = false;
	}
}

