#pragma once

struct Player
{
	int lives;
};

Player InitDefaultPlayer();
bool IsAlive();
void CheckWin();