#include "ResultScene.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Utils.h"
#include "sl.h"
#include <iostream>
using namespace std;

namespace ResultScene
{
	static PlayerSpace::Player savedPlayer;
	static UIManager::Button exitButton;
	static UIManager::Button backToMenuButton;
	static UIManager::Text resultText;
	static string win = "WON!";
	static string lose = "LOST!";
	static short buttonsWidth = 150;
	static short biggerButtonsWidth = buttonsWidth*3;
	static short buttonsHeight = 40;

	static int buttonsPadding = 20;
	static int smallerFontSize = 30;
	static int defaultFontSize = 40;

	void SavePlayer(PlayerSpace::Player player)
	{
		savedPlayer = player;
	}

	void Init()
	{
		resultText = UIManager::GetText(Logic::screenWidth / 2, Logic::screenHeight / 2, defaultFontSize*2, "YOU ", ColorManager::RED, ColorManager::YELLOW);

		exitButton = UIManager::GetButton(Logic::screenWidth *6/8 - buttonsWidth / 2, buttonsHeight + buttonsPadding, buttonsWidth, buttonsHeight, "EXIT", ColorManager::BLACK, ColorManager::RED);
		backToMenuButton = UIManager::GetButton(Logic::screenWidth *2/8 - biggerButtonsWidth / 2, exitButton.shape.pos.y, biggerButtonsWidth, buttonsHeight, "BACK TO MENU", ColorManager::BLACK, ColorManager::PURPLE);
	
	}

	void Update()
	{
		if (UIManager::IsMouseOnButton(backToMenuButton))
		{
			backToMenuButton.currentColor = backToMenuButton.highlightColor;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				SceneManager::SetCurrentScene(SceneManager::Menu);
		}
		else
			backToMenuButton.currentColor = backToMenuButton.defaultColor;

		if (UIManager::IsMouseOnButton(exitButton))
		{
			exitButton.currentColor = exitButton.highlightColor;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				SceneManager::SetCurrentScene(SceneManager::None);
		}
		else
			exitButton.currentColor = exitButton.defaultColor;

		if (savedPlayer.won)
		{
			resultText.currentColor = resultText.alt2Color;
			resultText.content += win;
			savedPlayer.won = false;
		}
		else if (savedPlayer.lost)
		{
			resultText.currentColor = resultText.alt1Color;
			resultText.content += lose;
			savedPlayer.lost = false;
		}
	}

	void Draw()
	{
		UIManager::DrawButtonRect(backToMenuButton);
		UIManager::DrawButtonText(backToMenuButton);

		UIManager::DrawButtonRect(exitButton);
		UIManager::DrawButtonText(exitButton);
	
		UIManager::PrintText(resultText);
	}
}
