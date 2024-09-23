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
	static Text rulesTitle;
	static Text rule1;
	static Text rule2;
	static Text rule3;
	static Button backToMenuButton;

	static int titleSize = 40;
	static short buttonsWidth = 160;
	static short buttonsHeight = 30;
	static short rulesPadding = titleSize * 3;
 
	void Init()
	{
		rulesTitle = UIManager::GetText(screenWidth / 2, screenHeight - titleSize*2, titleSize, "RULES", BLUE);
		rule1 = UIManager::GetText(screenWidth / 2, rulesTitle.location.y - rulesPadding, titleSize / 2, "Move left to right with the ARROW KEYS", WHITE);
		rule2 = UIManager::GetText(screenWidth / 2, rule1.location.y - rulesPadding, titleSize / 2, "Break all the blocks to win", WHITE);
		rule3 = UIManager::GetText(screenWidth / 2, rule2.location.y - rulesPadding, titleSize / 2, "If you lose all 3 lives you lose", WHITE);
	
		backToMenuButton = UIManager::GetButton(screenWidth / 2 - buttonsWidth/2, titleSize, buttonsWidth, buttonsHeight, "BACK TO MENU", BLACK, PURPLE);
	}

	void Update()
	{
		if (UIManager::IsMouseOnButton(backToMenuButton))
		{
			backToMenuButton.currentColor = backToMenuButton.highlightColor;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				SceneManager::SetCurrentScene(SceneManager::Menu);
			}
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
		UIManager::DrawButtonText(backToMenuButton, WHITE, backToMenuButton.shape.height/2);
	}
}