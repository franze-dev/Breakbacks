#include "Player.h"

Player InitDefaultPlayer()
{
	Player myPlayer;
	myPlayer.lives = 3;
	return myPlayer;
}

void LooseLife(Player player)
{
	player.lives--;
}

bool IsAlive(Player player)
{
	if (player.lives <= 0)
	{
		player.lives = 0;
		return false;
	}
	return true;
}
