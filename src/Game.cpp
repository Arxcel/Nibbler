
#include "Game.hpp"


void mLog(std::string const & src)
{
	std::cout << src << std::endl;
}

Game::Game()
{
	mWidth = 800;
	mHeight = 600;
	if (loadAPI("nibbler_glfw/nibbler_glfw.so"))
		initApi(mWidth, mHeight, "Nibbler");
	mLevel.load("levels/level1", mWidth * 2, mHeight * 2);
	std::array<float, 2> pos{{static_cast<float>(mWidth), static_cast<float>(mHeight)}};
	mSnake = new Snake(pos, 40, 5);
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
	draw			= reinterpret_cast<drawFunction>(dlsym(mLib, "draw"));
	getUserInput	= reinterpret_cast<processInputFunction>(dlsym(mLib, "getInput"));
	deinitApi		= reinterpret_cast<deinitFunction>(dlsym(mLib, "deinitializeApi"));
	preFrame		= reinterpret_cast<preFrameFunction>(dlsym(mLib, "preFrame"));
	postFrame		= reinterpret_cast<postFrameFunction>(dlsym(mLib, "postFrame"));
	renderer		= reinterpret_cast<renderFunction >(dlsym(mLib, "renderer"));
	result &= (initApi != nullptr);
	result &= (draw != nullptr);
	result &= (getUserInput != nullptr);
	result &= (deinitApi != nullptr);
	if (!result)
		std::cerr << "dlsym : "<< dlerror() << std::endl;
	return result;
}


void	Game::processCommand(std::string const &aCommand)
{
	static_cast<void>(aCommand);
}

void Game::start()
{
	while (mIsRunning)
	{
		if (mState == GameState::GAME_ACTIVE)
		{
			preFrame();
			draw({{static_cast<float>(mWidth * 2), static_cast<float>(mHeight * 2)}});
			mLevel.draw(renderer);
			mSnake->draw(renderer);
			mSnake->move(1,1,1);
			postFrame();
		}
		auto command = getUserInput(mIsRunning);
		processCommand(command);
	}
}