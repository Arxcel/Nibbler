#include <random>
#include "Game.hpp"
#include "MediaAPI.hpp"

std::vector<std::string> cActions = { "UP", "DOWN", "RIGHT", "LEFT", "Faster", "Slower", "Pause", "LIB1", "LIB2", "LIB3"};

bool	Game::init(unsigned lib, int w, int h, int s, bool hardMod)
{
	try
	{
		mWidth = w;
		mHeight = h;
		mSize = s;
		mScore = 0;
		mApi = std::make_shared<MediaAPI>(mWidth, mHeight, lib);
		mCurrLib = static_cast<int>(lib);
		std::array<float, 2> pos{{static_cast<float>(mWidth % 2 == 0 ? mWidth : mWidth + 1), static_cast<float>(mHeight % 2 == 0 ? mHeight : mHeight + 1)}};
		mSnake = std::make_shared<Snake>(pos, mSize, 5);
		mBefore = std::chrono::high_resolution_clock::now();
		mLevel = std::make_shared<GameLevel>(mWidth * 2, mHeight * 2, mSize, hardMod);
		mCommands.clear();
		mState = GameState::GAME_START;
		addFood();
		return true;
	}
	catch (std::exception &e)
	{
		return false;
	}
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
		mApi->playAudio(1);
		mScore += 10;
		if (mScore % 100 == 0)
		{
			mSnake->getSpeed() += 3;
			mApi->playAudio(0);
		}
		addFood();
	}

	for (auto &brick : mLevel->bricks)
		if (checkCollision(snakeHead, brick))
		{
			mState = GameState::GAME_OVER;
			mApi->stopMusic();
		}

	for (auto &part : mSnake->mBody)
		if (part != snakeHead && checkCollision(snakeHead, part))
		{
			mState = GameState::GAME_OVER;
			mApi->stopMusic();
		}}

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

        for (auto &part : mLevel->bricks)
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
		int index = 0;
		for (auto &action : cActions)
		{
		    if(action == cmd)
		        break;
		    index++;
        }
        switch (index)
        {
            case 0:
                mSnake->setDirection(Direction::UP);
                break;
            case 1:
                mSnake->setDirection(Direction::BOTTOM);
                break;
            case 2:
                mSnake->setDirection(Direction::RIGHT);
                break;
            case 3:
                mSnake->setDirection(Direction::LEFT);
                break;
            case 4:
                mSnake->getSpeed()++;
                break;
            case 5:
                mSnake->getSpeed() = mSnake->getSpeed() - 1  > 0 ? mSnake->getSpeed() - 1 : mSnake->getSpeed();
                break;
            case 6:
                if (mState == GameState::GAME_OVER)
                {
                    mPostAction = mCurrLib;
                    mIsRunning = false;
                }
                else
                    mState = mState == GameState::GAME_PAUSED || mState == GAME_START ? GameState::GAME_ACTIVE : GameState::GAME_PAUSED;
                break;
            default:
                if (cmd == "LIB1" || cmd == "LIB2" || cmd == "LIB3")
                {
                    mPostAction = (cmd[3] - 48);
                    mIsRunning = false;
                }
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
		mApi->preFrame();
		if (mState == GameState::GAME_ACTIVE)
		{
			move();
			update();
			mLevel->draw(mApi);
			mSnake->draw(mApi);
			mApi->putText("Score: " + std::to_string(mScore), 5, 5, 0.7, {{1, 1, 1}});
			mApi->putText("Speed: " + std::to_string(mSnake->getSpeed()), 5, mHeight - 24 * 0.7f, 0.7, {{1, 1, 1}});
		}
		else if (mState == GameState::GAME_START)
		{
			mApi->putText("Press 'SPACE' to start", mWidth / 2.0f- 125, mHeight / 2.0f, 1, {{1, 0.5, 0.5}});
		}
		else if (mState == GameState::GAME_PAUSED)
		{
			mLevel->draw(mApi);
			mSnake->draw(mApi);
			mApi->putText("Score: " + std::to_string(mScore), 5, 5, 0.7, {{1, 1, 1}});
			mApi->putText("Paused", mWidth / 2.0f - 75, mHeight / 2.0f - 30, 2, {{1, 0.5, 0.5}});
		}
		else if (mState == GameState::GAME_OVER)
		{
			mApi->putText("GAME is OVER", mWidth / 2.0f - 200, mHeight / 2.0f - 30, 1.5, {{1, 0.5, 0.5}});
			mApi->putText("Final score: " + std::to_string(mScore), mWidth / 2.0f - 200, mHeight / 2.0f + 30, 1, {{1, 0.5, 0.5}});
			mApi->putText("Press 'SPACE' to start 'New Game'", mWidth / 2.0f - 200, mHeight / 2.0f + 90, 1, {{1, 0.5, 0.5}});
		}
		mApi->postFrame();
		processCommand();
	}
	return static_cast<unsigned>(mPostAction);
}