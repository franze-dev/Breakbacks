#pragma once
#include "Utils.h"
#include "ColorManager.h"
#include <iostream>
using namespace std;

namespace UIManager
{
	enum class Fonts
	{
		mainFont,
		titleFont1,
		titleFont2
	};

	struct Rectangle
	{
		Logic::Vector2 pos;
		int height;
		int width;
	};

	struct Text
	{
		string content = " ";
		int fontSize = 0;
		Logic::Vector2 location;
		ColorManager::Colors currentColor;
		ColorManager::Colors alt1Color;
		ColorManager::Colors alt2Color;
	};

	struct Button
	{
		Rectangle shape;
		Text textShown;
		//If there are two texts possibilities in the same button, these are the two alternatives.
		string contentAlt1;
		string contentAlt2;
		//default color is the color that is used at first, before I change it for highlighting.
		ColorManager::Colors defaultColor;
		//This is the color when the user hovers the mouse over the button.
		ColorManager::Colors highlightColor;
		//The current color switches between the default color and the highlight
		ColorManager::Colors currentColor;
	};

	//Detects the mouse inside the bounds of a button
	bool IsMouseOnButton(Button button);
	//Draws the text in a button, as well as automatically centering it.
	void DrawButtonText(Button button);
	//Draws the square of the button
	void DrawButtonRect(Button button);
	//Prints a text
	void PrintText(Text myText, int align);
	//When I need to use a specific font, this is used
	void PrintText(Text myText, int align, Fonts font);
	//If I just need to print a quick text in the center and witht the default font, I use this
	void PrintText(Text myText);
	//Inits the fonts
	void InitFonts();
	//Create texts
	Text GetText(float x, float y, int fontSize, string content, ColorManager::Colors color);
	//If the text is the same and only the color changes at one point, then this is used.
	//color1 is the current color.
	Text GetText(float x, float y, int fontSize, string content, ColorManager::Colors color1, ColorManager::Colors color2);
	//Create buttons
	Button GetButton(float x, float y, int width, int height, string content, int fontSize, ColorManager::Colors mainColor, ColorManager::Colors highlightColor);

	//get the width of a text
	double GetTextWidth(string content, int fontSize, Fonts font);
	//in case I do have a text defined and I want to know the width
	double GetTextWidth(Text text, Fonts font);
	//get the height of a text
	double GetTextHeight(string content, int fontSize, Fonts font);
	double GetTextHeight(Text text, Fonts font);
}
