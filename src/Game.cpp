#include <chrono>
#include "Game.hpp"


void mLog(std::string const & src)
{
	std::cout << src << std::endl;
}

Game::Game()
{
	mWidth = 800;
	mHeight = 600;
	mSize  = 50;
	if (loadAPI("nibbler_glfw/nibbler_glfw.so"))
		initApi(mWidth, mHeight, "Nibbler");
	std::array<float, 2> pos{{static_cast<float>(mWidth), static_cast<float>(mHeight)}};
	mSnake = new Snake(pos, mSize, 5);
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
	initApi			= reinterpret_cast<initFunction>(dlsym(mLib, "initializeApi"));
	getUserInput	= reinterpret_cast<processInputFunction>(dlsym(mLib, "getInput"));
	deinitApi		= reinterpret_cast<deinitFunction>(dlsym(mLib, "deinitializeApi"));
	preFrame		= reinterpret_cast<preFrameFunction>(dlsym(mLib, "preFrame"));
	postFrame		= reinterpret_cast<postFrameFunction>(dlsym(mLib, "postFrame"));
	renderer		= reinterpret_cast<renderFunction >(dlsym(mLib, "renderer"));
	result &= (initApi != nullptr);
//	result &= (draw != nullptr);
	result &= (getUserInput != nullptr);
	result &= (deinitApi != nullptr);
	result &= (preFrame != nullptr);
	result &= (postFrame != nullptr);
	result &= (renderer != nullptr);

	if (!result)
		std::cerr << "dlsym : "<< dlerror() << std::endl;
	return result;
}


void	Game::processCommand(std::string const &aCommand)
{
	if (aCommand == "UP")
		mSnake->setDirection(Direction::UP);
	else if (aCommand == "DOWN")
		mSnake->setDirection(Direction::BOTTOM);
	else if (aCommand == "RIGHT")
		mSnake->setDirection(Direction::RIGHT);
	else if (aCommand == "LEFT")
		mSnake->setDirection(Direction::LEFT);
}

void Game::start()
{
	auto before = std::chrono::high_resolution_clock::now();
	while (mIsRunning)
	{
		if (mState == GameState::GAME_ACTIVE)
		{
			preFrame();
			mSnake->draw(renderer);
			std::chrono::milliseconds delta(1000);
			if (std::chrono::high_resolution_clock::now() > (before + delta))
			{
				mSnake->move();
				before = std::chrono::high_resolution_clock::now();
			}
			postFrame();
		}
		auto command = getUserInput(mIsRunning);
		processCommand(command);
	}
}