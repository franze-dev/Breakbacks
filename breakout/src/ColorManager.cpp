#include "ColorManager.h"
#include "sl.h"

static Color white;
static Color red;
static Color orange;
static Color yellow;
static Color green;
static Color blue;
static Color purple;
static Color black;

static Color GetColor(int r, int g, int b);

static Color GetColor(int r, int g, int b)
{
	Color myColor;
	myColor.a = 1.0;
	myColor.r = r;
	myColor.g = g;
	myColor.b = b;

	return myColor;
}

void InitColors()
{
	white = GetColor(1.0, 1.0, 1.0);
	red = GetColor(1.0, 0.0, 0.0);
	yellow = GetColor(1.0, 1.0, 0.0);
	green = GetColor(0.0, 1.0, 0.0);
	blue = GetColor(0.0, 0.0, 1.0);
	purple = GetColor(1.0, 0.0, 1.0);
	black = GetColor(0.0, 0.0, 0.0);
}

Color GetColor(Colors color)
{
	Color myColor = white;

	switch (color)
	{
	case WHITE:
		myColor = white;
		break;
	case RED:
		myColor = red;
		break;
	case YELLOW:
		myColor = yellow;
		break;
	case GREEN:
		myColor = green;
		break;
	case BLUE:
		myColor = blue;
		break;
	case PURPLE:
		myColor = purple;
		break;
	case BLACK:
		myColor = black;
		break;
	default:
		break;
	}

	return myColor;
}

void SetForeColor(Colors color)
{
	Color myColor = GetColor(color);
	
	slSetForeColor(myColor.r, myColor.g, myColor.b, myColor.a);
}
