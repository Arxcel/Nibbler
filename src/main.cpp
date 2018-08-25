#include "Game.hpp"

int main()
{
	unsigned k = 0;
	while (k != -1)
	{
			Game game(k);
			k = game.start();
	}
	return 0;

}
