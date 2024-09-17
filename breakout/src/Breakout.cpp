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

		slLoadFont("fonts/RubikMonoOne-Regular.ttf");

		InitColors();

		if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
			GameplayScene::Init();
	}

	void Update()
	{
		if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
			GameplayScene::Update();
	}

	void Draw()
	{
		if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
			GameplayScene::Draw();
	}

	void Close()
	{
		slClose();
	}

}
