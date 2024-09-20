#include "UIManager.h"
#include "sl.h"


namespace UIManager
{
	static int mainFont;
	
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
		slSetFont(mainFont, fontSize);
		double posX = button.shape.pos.x + button.shape.width / 2;
		double posY = button.shape.pos.y + button.shape.height / 2 - fontSize * 2/5;
		slText(posX, posY, button.textShown.data());
	}

	void DrawButtonRect(Button button)
	{
		SetForeColor(button.currentColor);
		slRectangleFill(button.shape.pos.x+button.shape.width/2, button.shape.pos.y + button.shape.height/2, button.shape.width, button.shape.height);
	}

	void PrintText(Text myText)
	{
		SetForeColor(myText.alt1Color);
		slSetFont(mainFont, myText.fontSize);
		slSetTextAlign(SL_ALIGN_CENTER);
		slText(myText.location.x, myText.location.y, myText.content.data());
	}
	
	void InitMainFont()
	{
		mainFont = slLoadFont("res/fonts/RubikMonoOne-Regular.ttf");
	}
}

