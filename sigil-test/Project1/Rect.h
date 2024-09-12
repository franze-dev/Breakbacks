#pragma once
#include "Utils.h"

struct Rect
{
	Vector2 pos;
	int height;
	int width;
	float speed;
};

namespace RectSpace
{
	Rect GetDefaultRect();
	void DrawRect(Rect myRect);
	void MoveRect(Rect& myRect);
};

