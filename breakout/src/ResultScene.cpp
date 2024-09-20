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
		exitButton.defaultColor = BLACK;
		exitButton.shape.width = 150;
		exitButton.shape.height = 50;
		exitButton.currentColor = exitButton.defaultColor;
		exitButton.shape.pos.x = screenWidth /2 - exitButton.shape.width/2;
		exitButton.shape.pos.y += exitButton.shape.height + buttonsPadding;
		exitButton.textShown = "EXIT";
		exitButton.highlightColor = RED;
#pragma endregion

#pragma region RESULT_TEXT
		resultText.alt1Color = RED;
		resultText.alt2Color = YELLOW;
		resultText.currentColor = resultText.alt1Color;
		resultText.content = "YOU ";
		resultText.fontSize = 50;
		resultText.location.x = screenWidth / 2;
		resultText.location.y = screenHeight / 2;
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
		UIManager::DrawButtonRect(exitButton);
		UIManager::DrawButtonText(exitButton, WHITE, defaultFontSize);
		UIManager::PrintText(resultText);
	}
}
