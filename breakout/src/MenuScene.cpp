#include <iostream>
#include <string>
#include "MenuScene.h"
#include "SceneManager.h"
#include "UIManager.h"
using namespace std;

namespace MenuScene
{
	static Button playButton;
	static Button exitButton;
	static Button rulesButton;

	static Text titlePart1;
	static Text titlePart2;

	static short defaultFontSize = 40;
	//space between buttons
	static short buttonsPadding = 60;
	static short titlePadding = 10;
	static short buttonsWidth = 180;
	static short buttonsHeight = 40;

	void Init()
	{
		titlePart1 = UIManager::GetText(screenWidth / 2, screenHeight - defaultFontSize * 2 - titlePadding, defaultFontSize * 2, "BREAK", PURPLE);
		titlePart2 = UIManager::GetText(titlePart1.location.x, screenHeight - titlePart1.fontSize * 3 + titlePadding * 2, titlePart1.fontSize * 2, "BACKS", PURPLE);

		playButton = UIManager::GetButton(screenWidth / 2 - buttonsWidth / 2, titlePart2.location.y - buttonsWidth / 2, buttonsWidth, buttonsHeight, "PLAY", BLACK, PURPLE);
		exitButton = UIManager::GetButton(playButton.shape.pos.x, playButton.shape.pos.y - playButton.shape.height*2 - buttonsPadding, buttonsWidth, buttonsHeight, "EXIT", BLACK, RED);
		rulesButton = UIManager::GetButton(playButton.shape.pos.x, exitButton.shape.pos.y + exitButton.shape.height + buttonsPadding/2, buttonsWidth, buttonsHeight, "RULES", BLACK, BLUE);
	}

	void Update()
	{
		if (UIManager::IsMouseOnButton(playButton))
		{
			playButton.currentColor = playButton.highlightColor;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				SceneManager::SetCurrentScene(SceneManager::Gameplay);
		}
		else
			playButton.currentColor = playButton.defaultColor;

		if (UIManager::IsMouseOnButton(exitButton))
		{
			exitButton.currentColor = exitButton.highlightColor;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				SceneManager::SetCurrentScene(SceneManager::None);
		}
		else
			exitButton.currentColor = exitButton.defaultColor;

		if (UIManager::IsMouseOnButton(rulesButton))
		{
			rulesButton.currentColor = rulesButton.highlightColor;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				SceneManager::SetCurrentScene(SceneManager::Rules);
		}
		else
			rulesButton.currentColor = rulesButton.defaultColor;
	}

	void Draw()
	{
		UIManager::PrintText(titlePart1, SL_ALIGN_CENTER, Fonts::titleFont1);
		UIManager::PrintText(titlePart2, SL_ALIGN_CENTER, Fonts::titleFont2);

		UIManager::DrawButtonRect(playButton);
		UIManager::DrawButtonRect(exitButton);
		UIManager::DrawButtonRect(rulesButton);

		UIManager::DrawButtonText(playButton);
		UIManager::DrawButtonText(exitButton);
		UIManager::DrawButtonText(rulesButton);
	}
}