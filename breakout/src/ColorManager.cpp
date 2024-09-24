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
static Color darkGray;
static Color pink;

static Color GetColor(double r, double g, double b)
{
	Color myColor;
	myColor.a = 1.0f;
	myColor.r = r;
	myColor.g = g;
	myColor.b = b;

	return myColor;
}

static Color GetColor(double r, double g, double b, double a)
{
	Color myColor;
	myColor.a = a;
	myColor.r = r;
	myColor.g = g;
	myColor.b = b;

	return myColor;
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
	case DARKGRAY:
		myColor = darkGray;
		break;
	case PINK:
		myColor = pink;
	default:
		break;
	}

	return myColor;
}

void InitColors()
{
	white = GetColor(1.0f, 1.0f, 1.0f);
	red = GetColor(1.0f, 0.0f, 0.0f);
	yellow = GetColor(1.0f, 1.0f, 0.0f);
	green = GetColor(0.0f, 1.0f, 0.0f);
	blue = GetColor(0.0f, 0.0f, 1.0f);
	purple = GetColor(1.0f, 0.0f, 1.0f);
	pink = GetColor(1.0f, 0.36f, 0.96f);
	black = GetColor(0.0f, 0.0f, 0.0f);
	darkGray = GetColor(0.42f, 0.42f, 0.42f, 0.98f);
}


void SetForeColor(Colors color)
{
	Color myColor = GetColor(color);
	
	slSetForeColor(myColor.r, myColor.g, myColor.b, myColor.a);
}
