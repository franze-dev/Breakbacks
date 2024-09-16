#include "UIManager.h"
#include "sl.h"

namespace UIManager
{
	bool UIManager::IsMouseOnButton(Button button)
	{
		if (slGetMouseX() > button.shape.pos.x &&
			slGetMouseY() > button.shape.pos.y &&
			slGetMouseX() < (button.shape.pos.x + button.shape.width) &&
			slGetMouseY() < (button.shape.pos.y + button.shape.height))
		{
			return true;
		}
		return false;
	}

	void UIManager::DrawButtonText(Button button, Color textColor, int fontSize)
	{
		DrawText(button.textShown.data(), button.shape.pos.x + button.shape.width / 2 - MeasureText(button.textShown.data(), fontSize) / 2, button.shape.pos.y + button.shape.height / 2 - fontSize / 2, fontSize, textColor);
	}

	void UIManager::DrawButtonRect(Button button)
	{
		DrawRectangle(button.shape.x, button.shape.y, button.shape.width, button.shape.height, button.currentColor);
	}

	void UIManager::PrintText(Text myText)
	{
		DrawText(myText.content.data(), myText.location.x, myText.location.y, myText.fontSize, myText.color);
	}

	void UIManager::PrintText(Text myText, int score)
	{
		DrawText(TextFormat(myText.content.data(), score), myText.location.x, myText.location.y, myText.fontSize, myText.color); // PLAYER 1
	}
}

