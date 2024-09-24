#pragma once

enum Colors
{
	RED,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE,
	PINK,
	WHITE,
	BLACK,
	DARKGRAY
};

struct Color
{
	double r;
	double g;
	double b;
	double a;
};

void InitColors();
Color GetColor(Colors color);
void SetForeColor(Colors color);

