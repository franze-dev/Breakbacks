#include "sl.h"
#include "Utils.h"
#include "Breakout.h"
#include "SceneManager.h"
#include "GameplayScene.h"
#include "ColorManager.h"
#include "ResultScene.h"
#include "UIManager.h"
#include "MenuScene.h"

namespace Breakout
{
	void Init();
	void Update();
	void Draw();
	void Close();
	bool ShouldWindowClose();

	void Play()
	{
		Init();

		while (!ShouldWindowClose())
		{
			Update();
			Draw();

			slRender();
		}
		Close();
	}

	void Init()
	{
		slWindow(screenWidth, screenHeight, "BREAKBACKS", 0);

		UIManager::InitFonts();

		InitColors();

		GameplayScene::Init();
		ResultScene::Init();
		MenuScene::Init();
	}

	void Update()
	{
		if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
			GameplayScene::Update();

		if (SceneManager::GetCurrentScene() == SceneManager::Result)
			ResultScene::Update();

		if (SceneManager::GetCurrentScene() == SceneManager::Menu)
			MenuScene::Update();
	}

	void Draw()
	{
		if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
			GameplayScene::Draw();

		if (SceneManager::GetCurrentScene() == SceneManager::Result)
			ResultScene::Draw();
		
		if (SceneManager::GetCurrentScene() == SceneManager::Menu)
			MenuScene::Draw();
	}

	void Close()
	{
		slClose();
	}

	bool ShouldWindowClose()
	{
		return (slShouldClose() || slGetKey(SL_KEY_ESCAPE) || SceneManager::GetCurrentScene() == SceneManager::None);
	}
}
