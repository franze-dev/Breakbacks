#include "sl.h"
#include "Utils.h"
#include "Breakout.h"
#include "SceneManager.h"
#include "GameplayScene.h"
#include "ColorManager.h"
#include "ResultScene.h"
#include "UIManager.h"
#include "MenuScene.h"
#include "RulesScene.h"

namespace Breakout
{
	static SceneManager::Scene previousScene = SceneManager::None;
	static bool restart = true;

	void Init();
	void Update();
	void Draw();
	void Close();
	bool ShouldWindowClose();

	void Play()
	{
		slWindow(Logic::screenWidth, Logic::screenHeight, "BREAKBACKS", 0);

		srand(time(0));

		while (!ShouldWindowClose())
		{
			//Here I try to verify that the values must be initialized again, this would only happen
			//when I press a "backToMenu" button. They exist in Gameplay and Result.
			if ((previousScene == SceneManager::Result || previousScene == SceneManager::Gameplay) &&
				SceneManager::GetCurrentScene() != SceneManager::Result &&
				SceneManager::GetCurrentScene() != SceneManager::Gameplay)
			{
				restart = true;
				previousScene = SceneManager::None;
			}

			if (restart)
			{
				Init();
				restart = false;
			}

			Update();
			Draw();

			slRender();
		}
		Close();
	}

	void Init()
	{

		UIManager::InitFonts();

		ColorManager::InitColors();

		GameplayScene::Init();
		ResultScene::Init();
		MenuScene::Init();
		RulesScene::Init();
	}

	void Update()
	{
		if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
		{
			GameplayScene::Update();

			if (previousScene != SceneManager::Gameplay)
				previousScene = SceneManager::Gameplay;
		}

		if (SceneManager::GetCurrentScene() == SceneManager::Result)
		{
			ResultScene::Update();
			if (previousScene != SceneManager::Result)
				previousScene = SceneManager::Result;
		}

		if (SceneManager::GetCurrentScene() == SceneManager::Menu)
			MenuScene::Update();

		if (SceneManager::GetCurrentScene() == SceneManager::Rules)
			RulesScene::Update();
	}

	void Draw()
	{
		if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
			GameplayScene::Draw();

		if (SceneManager::GetCurrentScene() == SceneManager::Result)
			ResultScene::Draw();
		
		if (SceneManager::GetCurrentScene() == SceneManager::Menu)
			MenuScene::Draw();

		if (SceneManager::GetCurrentScene() == SceneManager::Rules)
			RulesScene::Draw();
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
