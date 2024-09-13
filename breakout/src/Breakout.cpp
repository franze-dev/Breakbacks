#include "sl.h"
#include "Utils.h"
#include "Breakout.h"
#include "SceneManager.h"
#include "GameplayScene.h"
#include "ColorManager.h"

namespace Breakout
{
	void Init();
	void Update();
	void Draw();
	void Close();
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
	Breakout::Close();
}

void Breakout::Init()
{
	slWindow(screenWidth, screenHeight, "BREAKBACKS", 0);

	InitColors();

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

void Breakout::Close()
{
	slClose();
}

