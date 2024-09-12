#pragma once
//I will need it soon 

enum KeyStates
{
	none,
	pressed,
	released
	//if it was pressed, and it's STILL PRESSED, then it's "IsKeyDown()"
	//if it was pressed, and NOW IT'S RELEASED, then it's "IsKeyReleased()"
	//if it was released and NOW IT'S RELEASED, then it's NONE.
};

void UpdateStates();
bool IsKeyPressed();
bool IsKeyReleased();