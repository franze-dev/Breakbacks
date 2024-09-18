#include "ResultScene.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Utils.h"
#include "sl.h"
#include <iostream>
using namespace std;

namespace ResultScene
{
	static Player savedPlayer;
	static Button exitButton;
	static Text resultText;
	static string win = "WON!";
	static string lose = "LOST!";

	static int buttonsPadding = 20;
	static int smallerFontSize = 15;
	static int defaultFontSize = 40;

	void SavePlayer(Player player)
	{
		savedPlayer = player;
	}

	void Init()
	{
#pragma region EXIT_BUTTON
		exitButton.shape.width = 150;
		exitButton.shape.height = 30;
		exitButton.defaultColor = BLACK;
		exitButton.currentColor = exitButton.defaultColor;
		exitButton.shape.pos.x = screenWidth * 3 / 8;
		exitButton.shape.pos.y += exitButton.shape.height + buttonsPadding;
		exitButton.textShown = "EXIT";
		exitButton.highlightColor = RED;
#pragma endregion

#pragma region RESULT_TEXT
		resultText.color = RED;
		resultText.content = "YOU ";
		resultText.fontSize = 50;
		resultText.location.x = screenWidth / 2;//- slGetTextWidth(resultText.content.c_str()) / 2;
		resultText.location.y = screenHeight / 2;// - slGetTextHeight(resultText.content.c_str()) / 2;
#pragma endregion


	}

	void Update()
	{
		/*if (IsMouseOnButton(backToMenuButton))
		{
			backToMenuButton.currentColor = backToMenuButton.highlightColor;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				SceneManager::SetCurrentScene(Menu);
		}
		else
			backToMenuButton.currentColor = backToMenuButton.defaultColor;*/

		if (UIManager::IsMouseOnButton(exitButton))
		{
			exitButton.currentColor = exitButton.highlightColor;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				SceneManager::SetCurrentScene(SceneManager::None);
		}
		else
			exitButton.currentColor = exitButton.defaultColor;

		if (savedPlayer.won)
			resultText.content += win;
		else if (savedPlayer.lost)
			resultText.content += lose;
	}

	void Draw()
	{

		if (savedPlayer.won)
			resultText.content += win;
		else if (savedPlayer.lost)
			resultText.content += lose;

		UIManager::DrawButtonRect(exitButton);
		UIManager::DrawButtonText(exitButton, WHITE, smallerFontSize);
		UIManager::PrintText(resultText);
	}
}
