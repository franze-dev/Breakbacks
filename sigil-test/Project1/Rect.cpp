#include "Rect.h"
#include "Constants.h"

Rect GetDefaultRect()
{
	Rect myRect;
	myRect.width = 200;
	myRect.height = 10;
	myRect.x = screenHalfWidth;
	myRect.y = 0 + myRect.height;
	return myRect;
}