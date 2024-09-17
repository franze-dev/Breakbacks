#include "ResultScene.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Utils.h"
#include "sl.h"
#include <iostream>
using namespace std;

namespace ResultScene
{
	static Player savedPlayer1;
	static Button exitButton;

	static int buttonsPadding = 20;
	static int smallerFontSize = 15;
	static int defaultFontSize = 40;

	void SavePlayer(Player player)
	{
		savedPlayer1 = player;
	}

	void Init()
	{
		exitButton.shape.pos.x = screenWidth * 3 / 8;
		exitButton.shape.width = 150;
		exitButton.shape.height = 30;
		exitButton.defaultColor = BLACK;
		exitButton.currentColor = exitButton.defaultColor;
		exitButton.shape.pos.y += exitButton.shape.height + buttonsPadding;
		exitButton.textShown = "EXIT";
		exitButton.highlightColor = RED;
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
	}

	void Draw()
	{
		string winner = " ";

		if (savedPlayer1.score > savedPlayer2.score)
			winner = savedPlayer1.name;
		else
			winner = savedPlayer2.name;

		winner += " has won!";

		DrawText(winner.data(), GetScreenWidth() / 2 - MeasureText(winner.data(), defaultFontSize) / 2, GetScreenHeight() * 3 / 8, defaultFontSize, YELLOW);

		DrawButtonRect(backToMenuButton);
		DrawButtonText(backToMenuButton, WHITE, smallerFontSize);

		DrawButtonRect(exitButton);
		DrawButtonText(exitButton, WHITE, smallerFontSize);
	}
}
