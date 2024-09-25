#include "PauseMenu.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "GameplayScene.h"
#include "Utils.h"

namespace PauseMenu
{
	UIManager::Text pauseTitle;
	UIManager::Button continueButton;
	UIManager::Button backToMenuButton;

	int defaultFontSize = 40;
	int buttonsPadding = 30;

	void Init()
	{

		pauseTitle = UIManager::GetText(Logic::screenWidth * 2 / 8, Logic::screenHeight / 2 + defaultFontSize * 2, defaultFontSize, "PAUSED", ColorManager::BLACK);

		continueButton = UIManager::GetButton(Logic::screenWidth * 5 / 8, pauseTitle.location.y + pauseTitle.fontSize,
			UIManager::GetTextWidth(pauseTitle, UIManager::Fonts::mainFont) + 10, defaultFontSize, "CONTINUE", ColorManager::BLACK, ColorManager::PURPLE);

		backToMenuButton = UIManager::GetButton(Logic::screenWidth * 5 / 8, pauseTitle.location.y - pauseTitle.fontSize,
			UIManager::GetTextWidth(pauseTitle, UIManager::Fonts::mainFont) + 10, defaultFontSize, "BACK TO MENU", ColorManager::BLACK, ColorManager::BLUE);

	}

	void Update()
	{
		if (UIManager::IsMouseOnButton(continueButton))
		{
			continueButton.currentColor = continueButton.highlightColor;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				GameplayScene::UnPauseGame();
		}
		else
			continueButton.currentColor = continueButton.defaultColor;

		if (UIManager::IsMouseOnButton(backToMenuButton))
		{
			backToMenuButton.currentColor = backToMenuButton.highlightColor;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
				SceneManager::SetCurrentScene(SceneManager::Menu);
		}
		else
			backToMenuButton.currentColor = backToMenuButton.defaultColor;

	}

	void Draw()
	{
		UIManager::PrintText(pauseTitle);

		UIManager::DrawButtonRect(continueButton);
		UIManager::DrawButtonRect(backToMenuButton);
		UIManager::DrawButtonText(continueButton);
		UIManager::DrawButtonText(backToMenuButton);
	}
}

