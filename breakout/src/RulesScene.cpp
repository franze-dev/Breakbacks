#include "RulesScene.h"
#include "UIManager.h"
#include "SceneManager.h"

//	RULES
//	
//	- Move left to right(< -->).
//	- Break all the blocks to win.
//	- If you lose all 3 lives you lose.

namespace RulesScene
{
	static UIManager::Text rulesTitle;
	static UIManager::Text rule1;
	static UIManager::Text rule2;
	static UIManager::Text rule3;
	static UIManager::Button backToMenuButton;

	static int titleSize = 40;
	static short buttonsWidth = 160;
	static short buttonsHeight = 30;
	static short rulesPadding = titleSize * 3;
 
	void Init()
	{
		rulesTitle = UIManager::GetText(Logic::screenWidth / 2, Logic::screenHeight - titleSize*2, titleSize, "RULES", ColorManager::BLUE);
		rule1 = UIManager::GetText(Logic::screenWidth / 2, rulesTitle.location.y - rulesPadding, titleSize / 2, "Move left to right with the ARROW KEYS", ColorManager::WHITE);
		rule2 = UIManager::GetText(Logic::screenWidth / 2, rule1.location.y - rulesPadding, titleSize / 2, "Break all the blocks to win", ColorManager::WHITE);
		rule3 = UIManager::GetText(Logic::screenWidth / 2, rule2.location.y - rulesPadding, titleSize / 2, "If you miss the ball 3 times you lose", ColorManager::WHITE);
	
		backToMenuButton = UIManager::GetButton(Logic::screenWidth / 2 - buttonsWidth/2, titleSize, buttonsWidth, buttonsHeight, "BACK TO MENU", ColorManager::BLACK, ColorManager::PURPLE);
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
	}

	void Draw()
	{
		UIManager::PrintText(rulesTitle);
		UIManager::PrintText(rule1);
		UIManager::PrintText(rule2);
		UIManager::PrintText(rule3);

		UIManager::DrawButtonRect(backToMenuButton);
		UIManager::DrawButtonText(backToMenuButton);
	}
}