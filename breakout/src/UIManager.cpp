#include "UIManager.h"
#include "sl.h"

namespace UIManager
{
	bool IsMouseOnButton(Button button)
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

	void DrawButtonText(Button button, Colors textColor, int fontSize)
	{
		SetForeColor(textColor);
		double posX = button.shape.pos.x + button.shape.width / 2 - slGetTextWidth(button.textShown.data()) / 2;
		double posY = button.shape.pos.y + button.shape.height / 2 - fontSize / 2;
		slText(posX, posY, button.textShown.data());
	}

	void DrawButtonRect(Button button)
	{
		SetForeColor(button.currentColor);
		slRectangleFill(button.shape.pos.x, button.shape.pos.y, button.shape.width, button.shape.height);
	}

	void PrintText(Text myText)
	{
		SetForeColor(myText.color);
		slText(myText.location.x, myText.location.y, myText.content.data());
	}

	//void UIManager::PrintText(Text myText, int score)
	//{
	//	DrawText(TextFormat(myText.content.data(), score), myText.location.x, myText.location.y, myText.fontSize, myText.color); // PLAYER 1
	//}
}

