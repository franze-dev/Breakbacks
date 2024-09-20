#pragma once
#include "Utils.h"
#include "ColorManager.h"
#include <iostream>
using namespace std;

	struct Rectangle
	{
		Vector2 pos;
		int height;
		int width;
	};

	struct Text
	{
		string content = " ";
		int fontSize = 0;
		Vector2 location;
		Colors currentColor;
		Colors alt1Color;
		Colors alt2Color;
	};

	struct Button
	{
		Rectangle shape;
		string textShown;
		//If there are two texts possibilities in the same button, these are the two alternatives.
		string textAlt1;
		string textAlt2;
		//If the button is a switch, it's convenient for it to have two colors that differenciate the 
		//status in which theyre in (on or off). I distinguish that with "defaultColor" and "secondDefaultColor"
		Colors defaultColor;
		Colors secondDefaultColor;
		//is it one color or another?
		bool activated = false;
		Colors currentColor;
		//This is the color when the user hovers the mouse over the button.
		Colors highlightColor;
	};

namespace UIManager
{
	//Detects the mouse inside the bounds of a button
	bool IsMouseOnButton(Button button);
	//Draws the text in a button, as well as automatically centering it.
	void DrawButtonText(Button button, Colors color, int fontSize);
	//Draws the square of the button
	void DrawButtonRect(Button button);
	//Prints a text
	void PrintText(Text myText, int align);
	//Inits the font
	void InitMainFont();
}
