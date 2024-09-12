#include "Breakout.h"
#include "SceneManager.h"
#include "GameplayScene.h"

namespace Breakout
{
	void Init();
	void Update();
	void Draw();
}

void Play()
{
	Breakout::Init();

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		Breakout::Update();
		Breakout::Draw();

		slRender();
	}
	slClose();
}

void Breakout::Init()
{
	slWindow(screenWidth, screenHeight, "BREAKBACKS", 0);

	if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
		GameplayScene::Init();
}

void Breakout::Update()
{
	if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
		GameplayScene::Update();
}

void Breakout::Draw()
{
	if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
		GameplayScene::Draw();
}

