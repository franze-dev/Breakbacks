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
	static UIManager::Text rule4;
	static UIManager::Text powerUpsTitle;
	static UIManager::Text powerConditionText;
	static UIManager::Text speedPowerText;
	static UIManager::Text sizePowerText;
	static UIManager::Text noBouncePowerText;
	static UIManager::Button backToMenuButton;

	static int titleSize = 40;
	static int textSize = titleSize / 3;
	static short buttonsWidth = 160;
	static short buttonsHeight = 30;
	static short rulesPadding = titleSize;
 
	void Init()
	{
		rulesTitle = UIManager::GetText(Logic::screenWidth / 2, Logic::screenHeight - titleSize*2, titleSize, "RULES", ColorManager::BLUE);
		rule1 = UIManager::GetText(Logic::screenWidth / 2, rulesTitle.location.y - rulesPadding, textSize, "Move left to right with the ARROW KEYS", ColorManager::WHITE);
		rule2 = UIManager::GetText(Logic::screenWidth / 2, rule1.location.y - rulesPadding, textSize, "Break all the blocks to win", ColorManager::WHITE);
		rule3 = UIManager::GetText(Logic::screenWidth / 2, rule2.location.y - rulesPadding, textSize, "If you miss the ball 3 times you lose", ColorManager::WHITE);
		rule4 = UIManager::GetText(Logic::screenWidth / 2, rule3.location.y - rulesPadding, textSize, "Press SPACE to launch the ball", ColorManager::WHITE);
	
		powerUpsTitle = UIManager::GetText(Logic::screenWidth / 2, rule4.location.y - rulesPadding *2, titleSize, "POWER-UPS", ColorManager::PURPLE);
		powerConditionText = UIManager::GetText(Logic::screenWidth / 2, powerUpsTitle.location.y - rulesPadding, textSize, "You can get one every 10 blocks that you break", ColorManager::WHITE);
		speedPowerText = UIManager::GetText(Logic::screenWidth / 2, powerConditionText.location.y - rulesPadding, textSize, "SPEED: The ball gets 100% faster", ColorManager::YELLOW);
		sizePowerText = UIManager::GetText(Logic::screenWidth / 2, speedPowerText.location.y - rulesPadding, textSize, "SIZE: The ball gets 3 times bigger", ColorManager::RED);
		noBouncePowerText = UIManager::GetText(Logic::screenWidth / 2, sizePowerText.location.y - rulesPadding, textSize, "NO BOUNCE: The ball doesn't bounce off the blocks", ColorManager::BLUE);
		
		
		backToMenuButton = UIManager::GetButton(Logic::screenWidth / 2 - buttonsWidth/2, titleSize, buttonsWidth, buttonsHeight, "BACK TO MENU", buttonsHeight/2, ColorManager::BLACK, ColorManager::PURPLE);
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
		UIManager::PrintText(rule4);

		UIManager::PrintText(powerUpsTitle);
		UIManager::PrintText(powerConditionText);
		UIManager::PrintText(speedPowerText);
		UIManager::PrintText(sizePowerText);
		UIManager::PrintText(noBouncePowerText);

		UIManager::DrawButtonRect(backToMenuButton);
		UIManager::DrawButtonText(backToMenuButton);
	}
}