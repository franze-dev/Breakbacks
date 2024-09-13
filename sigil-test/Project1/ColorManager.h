#pragma once

enum Colors
{
	WHITE,
	RED,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE
};

struct Color
{
	double r;
	double g;
	double b;
	double a;
};


void InitColors();
Color GetColor(int r, int g, int b);
Color GetColor(Colors color);
void SetForeColor(Colors color);

