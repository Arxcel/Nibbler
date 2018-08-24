#include "Game.hpp"

int main()
{
	while (1)
	{
		{
			Game game(1);
			game.start();
		}
		{
			Game game2(2);
			game2.start();
		}
		{
			Game game3(3);
			game3.start();
		}
	}
	return 0;

}
