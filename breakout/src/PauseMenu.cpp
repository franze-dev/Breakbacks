#include "PauseMenu.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "GameplayScene.h"
#include "Utils.h"

Text pauseTitle;
Button continueButton;
Button backToMenuButton;

int defaultFontSize = 40;
int buttonsPadding = 30;

void PauseMenu::Init()
{

	pauseTitle = UIManager::GetText(screenWidth * 2 / 8, screenHeight / 2 + defaultFontSize*2, defaultFontSize, "PAUSED", WHITE);

	continueButton = UIManager::GetButton(screenWidth * 5 / 8, pauseTitle.location.y + pauseTitle.fontSize,
								UIManager::GetTextWidth(pauseTitle, Fonts::mainFont), defaultFontSize, "CONTINUE", BLACK, PURPLE);

	backToMenuButton = UIManager::GetButton(screenWidth * 5 / 8, pauseTitle.location.y - pauseTitle.fontSize, 
								UIManager::GetTextWidth(pauseTitle, Fonts::mainFont), defaultFontSize, "BACK TO MENU", BLACK, BLUE);

}

void PauseMenu::Update()
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

void PauseMenu::Draw()
{
	UIManager::PrintText(pauseTitle);

	UIManager::DrawButtonRect(continueButton);
	UIManager::DrawButtonRect(backToMenuButton);
	UIManager::DrawButtonText(continueButton, WHITE, defaultFontSize / 2);
	UIManager::DrawButtonText(backToMenuButton, WHITE, defaultFontSize / 2);
}