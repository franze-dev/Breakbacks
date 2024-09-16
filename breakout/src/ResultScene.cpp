#include "ResultScene.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Utils.h"
#include <iostream>
using namespace std;

namespace ResultScene
{
	static Player savedPlayer1;
	static Button backToMenuButton;
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
		backToMenuButton.shape.x = screenWidth * 3 / 8;
		backToMenuButton.shape.y = screenHeight * 5 / 8;
		backToMenuButton.shape.width = 150;
		backToMenuButton.shape.height = 30;
		backToMenuButton.textShown = "BACK TO MENU";
		backToMenuButton.defaultColor = DARKGRAY;
		backToMenuButton.currentColor = backToMenuButton.defaultColor;
		backToMenuButton.highlightColor = BLUE;

		exitButton = backToMenuButton;
		exitButton.shape.y += exitButton.shape.height + buttonsPadding;
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

		if (IsMouseOnButton(exitButton))
		{
			exitButton.currentColor = exitButton.highlightColor;

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				SceneManager::SetCurrentScene(SceneManager::None);
		}
		else
			exitButton.currentColor = exitButton.defaultColor;
	}

	void Draw()
	{
		string winner = " ";

		DrawText(TextFormat("%02i", savedPlayer1.score), GetScreenWidth() * 3 / 8, GetScreenHeight() * 1 / 8, defaultFontSize, RED); // PLAYER 1
		DrawText(TextFormat("%02i", savedPlayer2.score), GetScreenWidth() * 4 / 8, GetScreenHeight() * 1 / 8, defaultFontSize, RED); // PLAYER 2
		DrawText(savedPlayer1.name.data(), GetScreenWidth() * 3 / 8, 10, defaultFontSize, WHITE);
		DrawText(savedPlayer2.name.data(), GetScreenWidth() * 4 / 8, 10, defaultFontSize, WHITE);

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
