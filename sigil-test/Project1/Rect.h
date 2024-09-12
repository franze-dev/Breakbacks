#pragma once
struct Rect
{
	int x;
	int y;
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

