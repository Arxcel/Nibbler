#include <random>
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
	mScore = 0;
	if (loadAPI("nibbler_sfml/nibbler_sfml.so"))
		initApi(mWidth, mHeight, "Nibbler");
	std::array<float, 2> pos{{static_cast<float>(mWidth), static_cast<float>(mHeight)}};
	mSnake = new Snake(pos, mSize, 5);
	mBefore = std::chrono::high_resolution_clock::now();
	mLevel = new GameLevel(mWidth * 2, mHeight * 2, mSize, 5);
	mCommands.clear();
	mState = GameState::GAME_MENU;
};

Game::~Game()
{
	deinitApi();
	if (mLib)
		dlclose(mLib);
	delete mSnake;
	delete mLevel;
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
	drawer			= reinterpret_cast<renderFunction >(dlsym(mLib, "draw"));
	putText			= reinterpret_cast<textFunction >(dlsym(mLib, "putText"));
	result &= (initApi != nullptr);
	result &= (getUserInput != nullptr);
	result &= (deinitApi != nullptr);
	result &= (preFrame != nullptr);
	result &= (postFrame != nullptr);
	result &= (drawer != nullptr);
	result &= (putText != nullptr);
	if (!result)
		std::cerr << "dlsym : "<< dlerror() << std::endl;
	return result;
}

bool	Game::checkCollision(GameObject *first, GameObject *second)
{
	if (first && second)
	{
		bool collisionX = first->x >= second->x && second->x >= first->x;
		bool collisionY = first->y >= second->y && second->y >= first->y;
		return collisionX && collisionY;
	}
	return false;
}

void	Game::update()
{
	GameObject *snakeHead = mSnake->mBody.front();
	if (checkCollision(mSnake->mBody.front(), mLevel->food.front()))
	{
		mLevel->food.clear();
		mSnake->grow();
		mScore += 10;
		if (mScore % 100 == 0)
			mSnake->getSpeed() += 3;
		addFood();
	}

	for (auto &brick : mLevel->bricks)
	{
		if (checkCollision(snakeHead, brick))
		{
			mIsRunning = false;
//			mState = GameState::GAME_OVER;
		}
	}

	for (auto &part : mSnake->mBody)
	{

		if (part != snakeHead && checkCollision(snakeHead, part))
		{
			mIsRunning = false;
//			mState = GameState::GAME_OVER;
		}
	}
}

void	Game::addFood()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> randX(1, mWidth * 2 / mSize - 2);
	std::uniform_int_distribution<int> randY(1, mHeight * 2 / mSize - 2);
	std::array<float, 3> color{{1.0f, 1.0f, 1.0f}};
	for (bool isPlaced = false; !isPlaced;)
	{
		auto food = new GameObject(6, randX(mt) * mSize, randY(mt) * mSize, mSize, 180, color);
		isPlaced = true;
		for (auto &part : mSnake->mBody)
		{
			if (checkCollision(food, part))
			{
				delete food;
				isPlaced = false;
				break;
			}
		}
		if (isPlaced)
			mLevel->addFood(food);
	}
}

void	Game::processCommand()
{
	if (!mCommands.empty())
	{
		auto first = mCommands.begin();
		auto cmd = *first;
		std::cout << cmd << std::endl;
		if (cmd == "UP")
			mSnake->setDirection(Direction::UP);
		else if (cmd == "DOWN")
			mSnake->setDirection(Direction::BOTTOM);
		else if (cmd == "RIGHT")
			mSnake->setDirection(Direction::RIGHT);
		else if (cmd == "LEFT")
			mSnake->setDirection(Direction::LEFT);
		else if (cmd == "Faster")
			mSnake->getSpeed()++;
		else if (cmd == "Slower")
			mSnake->getSpeed() = mSnake->getSpeed() - 1  > 0 ? mSnake->getSpeed() - 1 : mSnake->getSpeed();
		else if (cmd == "Pause")
			mState = mState == GameState::GAME_MENU || mState == GameState::GAME_OVER ? GameState::GAME_ACTIVE : GameState::GAME_MENU;
		mCommands.erase(first);
	}
}

void					Game::move()
{
	std::chrono::milliseconds delta((1000 / mSnake->getSpeed()));
	if (std::chrono::high_resolution_clock::now() > (mBefore + delta))
	{
		mSnake->move();
		mBefore = std::chrono::high_resolution_clock::now();
	}
}

void Game::start()
{
	addFood();
	while (mIsRunning)
	{
		const char *input = getUserInput(mIsRunning);
		if (input != nullptr)
		{
			mCommands.insert(std::string(input));
		}
		if (mState == GameState::GAME_ACTIVE)
		{
			preFrame();
			move();
			update();
			mLevel->draw(drawer);
			mSnake->draw(drawer);
			putText("Score: " + std::to_string(mScore), 5, 5, 0.7, {1, 1, 1});
			putText("Speed: " + std::to_string(mSnake->getSpeed()), 5, mHeight - 24 * 0.7f, 0.7, {1, 1, 1});
			postFrame();
		}
		else if (mState == GameState::GAME_MENU)
		{
			preFrame();
			mLevel->draw(drawer);
			mSnake->draw(drawer);
			putText("Score: " + std::to_string(mScore), 5, 5, 0.7, {1, 1, 1});
			putText("Paused", mWidth / 2 - 75, mHeight / 2 - 30, 2, {1, 0.5, 0.5});
			postFrame();
		}
		processCommand();
	}
}