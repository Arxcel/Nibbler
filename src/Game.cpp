
#include "Game.hpp"


void mLog(std::string const & src)
{
	std::cout << src << std::endl;
}

Game::Game()
{
	if (loadAPI("nibbler_glfw/nibbler_glfw.so"))
	{
		initApi(800, 600, "Nibbler");
	}
};

Game::~Game()
{
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
	result &= (initApi != nullptr);
	if (!initApi)
	{
		std::cerr << "dlsym : "<< dlerror() << std::endl;
	}
	return result;
}

void Game::start()
{
	while (mIsRunning)
	{
//		mDrawer->draw(mVertices);
//		processEvents();
	}
}