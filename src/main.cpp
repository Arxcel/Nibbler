#include "Game.hpp"
#include <string>

namespace
{
	void processCommand(int ac, char *av[], int &w, int &h, int &s, unsigned &lib)
	{
		w = 800;
		h = 600;
		s = 50;
		lib = 0;
		if (ac == 3)
		{
			std::string width(av[1]);
			std::string height(av[2]);
			int lW, lH, lS;
			try
			{
				lW = std::stoi(width) / 2;
				lH = std::stoi(height) / 2;
				lS = w / lW;
				if (lS > 5 && lS < 100 && lS * lH < 1200 && lH > 400)
				{
					h = lS * lH;
					s = lS;
					return;
				}
			}
			catch(...)
			{
			}
		}
		std::cout << "Not valid parameters.\nStarted with default parameters" << std::endl;
	}

}

int main(int ac, char *av[])
{
	int w{0},h{0},s{0};
	unsigned lib{0};

	processCommand(ac, av, w, h, s, lib);
	while (lib != -1)
	{
		std::cout << w << std::endl;
		std::cout << h << std::endl;
		std::cout << s << std::endl;
		Game game(lib, w, h, s);
		lib = game.start();
	}
	return 0;

}
