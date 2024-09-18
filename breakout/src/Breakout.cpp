#include "sl.h"
#include "Utils.h"
#include "Breakout.h"
#include "SceneManager.h"
#include "GameplayScene.h"
#include "ColorManager.h"
#include "ResultScene.h"
#include "UIManager.h"

namespace Breakout
{
	void Init();
	void Update();
	void Draw();
	void Close();

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

	void Init()
	{
		slWindow(screenWidth, screenHeight, "BREAKBACKS", 0);

		UIManager::InitMainFont();

		InitColors();

		GameplayScene::Init();
		ResultScene::Init();
	}

	void Update()
	{
		if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
			GameplayScene::Update();

		if (SceneManager::GetCurrentScene() == SceneManager::Result)
			ResultScene::Update();
	}

	void Draw()
	{
		if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
			GameplayScene::Draw();

		if (SceneManager::GetCurrentScene() == SceneManager::Result)
			ResultScene::Draw();
	}

	void Close()
	{
		slClose();
	}

}
