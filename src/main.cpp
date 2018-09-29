#include "Game.hpp"

namespace
{
	void processCommand(int ac, char *av[], int &w, int &h, int &s, unsigned &lib)
	{
		w = 800;
		h = 600;
		s = 50;
		lib = 0;
		bool success = false;
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
				if (lS > 10)
					lS = lS - lS % 10;
				if (lS > 9 && lS < 100 && lS * lH < 1200 && lS * lH > 400)
				{
					h = lS * lH;
					s = lS;
					success = true;
				}
			}
			catch(...)
			{}
			if (!success)
			{
				std::cerr << "ERROR: Not valid parameters." << std::endl;
				throw std::exception();
			}
		}
	}
}

int main(int ac, char *av[])
{
	int w{0}, h{0}, s{0};
	unsigned lib{0};
	try
	{
		processCommand(ac, av, w, h, s, lib);
		while (lib != static_cast<unsigned >(-1))
		{
			std::cout << w << std::endl;
			std::cout << h << std::endl;
			std::cout << s << std::endl;

			Game game;
			if (game.init(lib, w, h, s))
				lib = game.start();
			else
				break;
		}
	} catch (...)
	{}
	return 0;

}
