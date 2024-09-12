#include "GameplayScene.h"
#include "Rect.h"
#include "KeyManager.h"

static Rect mainRect;

void GameplayScene::Init()
{
	mainRect = RectSpace::GetDefaultRect();
}

void GameplayScene::Update()
{
	RectSpace::MoveRect(mainRect);
}

void GameplayScene::Draw()
{
	RectSpace::DrawRect(mainRect);
}
