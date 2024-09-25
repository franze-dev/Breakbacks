#pragma once

namespace PlayerSpace
{
	struct Player
	{
		int lives;
		bool won;
		bool lost;
	};

	Player InitDefaultPlayer();
	void LooseLife(Player& player);
	bool IsAlive(Player player);
}

