#pragma once

enum Colors
{
	WHITE,
	RED,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE,
	BLACK
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

