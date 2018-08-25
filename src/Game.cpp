#include <random>
#include "Game.hpp"
#include "DrawAPI.hpp"

Game::Game(unsigned lib, int w, int h, int s) : mWidth(w), mHeight(h), mSize(s), mScore(0)
{
	mApi = std::make_shared<DrawAPI>(mWidth, mHeight, lib);
	mCurrLib = static_cast<int>(lib);
	std::array<float, 2> pos{{static_cast<float>(mWidth), static_cast<float>(mHeight)}};
	mSnake = std::make_shared<Snake>(pos, mSize, 5);
	mBefore = std::chrono::high_resolution_clock::now();
	mLevel = std::make_shared<GameLevel>(mWidth * 2, mHeight * 2, mSize, 5);
	mCommands.clear();
	mState = GameState::GAME_START;
	addFood();
};

Game::Game()
{};

Game::~Game()
{};

Game::Game(Game const &)
{};

Game &Game::operator=(Game const &)
{
	return *this;
};

bool	Game::checkCollision(std::shared_ptr<GameObject> first, std::shared_ptr<GameObject> second)
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
	auto snakeHead = mSnake->mBody.front();
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
		if (checkCollision(snakeHead, brick))
			mState = GameState::GAME_OVER;

	for (auto &part : mSnake->mBody)
		if (part != snakeHead && checkCollision(snakeHead, part))
			mState = GameState::GAME_OVER;
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
		auto food = std::make_shared<GameObject>(6, randX(mt) * mSize, randY(mt) * mSize, mSize, 180, color);
		isPlaced = true;
		for (auto &part : mSnake->mBody)
		{
			if (checkCollision(food, part))
			{
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
		{
			if (mState == GameState::GAME_OVER)
			{
				mPostAction = mCurrLib;
				mIsRunning = false;
			}
			else
				mState = mState == GameState::GAME_PAUSED || mState == GAME_START ? GameState::GAME_ACTIVE : GameState::GAME_PAUSED;
		}
		else if (cmd == "LIB1" || cmd == "LIB2" || cmd == "LIB3")
		{
			mPostAction = (cmd[3] - 48);
			mIsRunning = false;
		}
		if (!mCommands.empty())
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

unsigned Game::start()
{
	while (mIsRunning)
	{
		auto input = mApi->getUserInput(mIsRunning);
		if (input != nullptr)
		{
			mCommands.insert(std::string(input));
		}
		if (mState == GameState::GAME_ACTIVE)
		{
			mApi->preFrame();

			move();
			update();
			mLevel->draw(mApi->drawer);
			mSnake->draw(mApi->drawer);
			mApi->putText("Score: " + std::to_string(mScore), 5, 5, 0.7, {1, 1, 1});
			mApi->putText("Speed: " + std::to_string(mSnake->getSpeed()), 5, mHeight - 24 * 0.7f, 0.7, {1, 1, 1});
			mApi->postFrame();
		}
		else if (mState == GameState::GAME_START)
		{
			mApi->preFrame();
			mApi->putText("Press 'SPACE' to start", mWidth / 2 - 125, mHeight / 2, 1, {1, 0.5, 0.5});
			mApi->postFrame();
		}
		else if (mState == GameState::GAME_PAUSED)
		{
			mApi->preFrame();
			mLevel->draw(mApi->drawer);
			mSnake->draw(mApi->drawer);
			mApi->putText("Score: " + std::to_string(mScore), 5, 5, 0.7, {1, 1, 1});
			mApi->putText("Paused", mWidth / 2 - 75, mHeight / 2 - 30, 2, {1, 0.5, 0.5});
			mApi->postFrame();
		}
		else if (mState == GameState::GAME_OVER)
		{
			mApi->preFrame();
			mApi->putText("GAME is OVER", mWidth / 2 - 200, mHeight / 2 - 30, 1.5, {1, 0.5, 0.5});
			mApi->putText("Final score: " + std::to_string(mScore), mWidth / 2 - 200, mHeight / 2 + 30, 1, {1, 0.5, 0.5});
			mApi->putText("Press 'SPACE' to start 'New Game'", mWidth / 2 - 200, mHeight / 2 + 90, 1, {1, 0.5, 0.5});
			mApi->postFrame();
		}
		processCommand();
	}
	return static_cast<unsigned>(mPostAction);
}