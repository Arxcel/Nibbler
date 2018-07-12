
#include "Game.hpp"


void mLog(std::string const & src)
{
	std::cout << src << std::endl;
}

Game::Game()
{
	if (loadAPI("nibbler_glfw/nibbler_glfw.so"))
		initApi(800, 600, "Nibbler");
};

Game::~Game()
{
	deinitApi();
	if (mLib)
		dlclose(mLib);
};

Game::Game(Game const &)
{
};

Game &Game::operator=(Game const &)
{
	return *this;
};

//void Game::processEvents()
//{
//	mKeyPressed = mDrawer->getKeyboardEvent();
//	if (mKeyPressed == KeyboardEvent::EXIT)
//		mIsRunning = false;
//}

bool Game::loadAPI(std::string const &path)
{
	bool result = true;
	if (mLib)
		dlclose(mLib);
	mLib = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!mLib)
	{
		std::cerr << "dlopen : "<< dlerror() << std::endl;
		return false;
	}
	initApi = reinterpret_cast<initFunction>(dlsym(mLib, "initializeApi"));
	draw = reinterpret_cast<drawFunction>(dlsym(mLib, "draw"));
	getUserInput = reinterpret_cast<processInputFunction>(dlsym(mLib, "getInput"));
	deinitApi = reinterpret_cast<deinitFunction>(dlsym(mLib, "deinitializeApi"));
	preFrame = reinterpret_cast<preFrameFunction>(dlsym(mLib, "preFrame"));
	postFrame = reinterpret_cast<postFrameFunction>(dlsym(mLib, "postFrame"));
	result &= (initApi != nullptr);
	result &= (draw != nullptr);
	result &= (getUserInput != nullptr);
	result &= (deinitApi != nullptr);
	if (!result)
		std::cerr << "dlsym : "<< dlerror() << std::endl;
	return result;
}

void Game::start()
{
	int i = 0;
	while (mIsRunning)
	{
		preFrame();
		int key = getUserInput(mIsRunning);
		if (key == 1)
			i++;
		draw(300 + i,300,2);
		postFrame();
	}
}