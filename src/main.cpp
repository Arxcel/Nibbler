#include "Game.hpp"

namespace
{
	bool processCommand(int ac, char *av[], int &w, int &h, int &s, unsigned &lib, bool &hardModOn)
	{
		w = 800;
		h = 600;
		s = 50;
		lib = 0;
        std::string mod;
		bool success = false;
		if (ac == 4)
            mod = av[3];
        if (ac == 3 || (ac == 4 && mod == "-h"))
		{
		    hardModOn = mod == "-h";
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
					w = lS * lW;
					s = lS;
					success = true;
				}
				else
				{
					if (lS <= 9)
						std::cerr << "Error: The map is too big." << std::endl;
					else if(lS >= 100)
						std::cerr << "Error: The map is too small." << std::endl;
					else if (lS * lH >= 1200 || lS * lH <= 400)
						std::cerr << "Error: Wrong width-height ratio." << std::endl;
				}
			}
			catch(...)
			{}
		} else {
			std::cerr << "Usage: ./nibbler width[18; 161] height[[12; 29]; [82; 239]] [-h]" << std::endl;
		}
        return success;
	}
}

// width [18; 161]
// width == 18  h[12; 29]
// width == 161 h[82; 239]
int main(int ac, char *av[])
{
	int w{0}, h{0}, s{0};
	unsigned lib{0};
	bool hardMod;
	try
	{
		if (processCommand(ac, av, w, h, s, lib, hardMod))
			while (lib != static_cast<unsigned >(-1))
			{
				Game game;
				if (game.init(lib, w, h, s, hardMod))
					lib = game.start();
				else
					break;
			}
	} catch (...)
	{}
	return 0;

}
