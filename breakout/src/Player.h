#pragma once

struct Player
{
	int lives;
};

Player InitDefaultPlayer();
void LooseLife(Player player);
bool IsAlive(Player player);
