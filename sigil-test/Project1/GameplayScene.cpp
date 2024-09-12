#include "GameplayScene.h"
#include "Rect.h"
#include "Ball.h"
#include "KeyManager.h"

static Rect mainRect;
static Ball mainBall;

void GameplayScene::Init()
{
	mainRect = RectSpace::GetDefaultRect();
	mainBall = BallSpace::GetDefaultBall();
}

void GameplayScene::Update()
{
	RectSpace::MoveRect(mainRect);
	BallSpace::CheckPlay(mainBall);
	if (!mainBall.reset)
	{
		BallSpace::MoveBall(mainBall);
	}
	else
		BallSpace::ResetBall(mainBall, mainRect);

	BallSpace::BallEdgeCollision(mainBall);
}

void GameplayScene::Draw()
{
	RectSpace::DrawRect(mainRect);
	BallSpace::DrawBall(mainBall);
}
