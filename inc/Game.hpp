//
// Created by Vadym KOZLOV on 7/7/18.
//

#ifndef NIBBLER_GAME_HPP
#define NIBBLER_GAME_HPP

#include <iostream>
#include <chrono>
#include "GameLevel.hpp"
#include "Snake.hpp"
#include <unordered_set>

enum GameState {
	GAME_START,
	GAME_ACTIVE,
	GAME_PAUSED,
	GAME_OVER
};

class DrawAPI;
class Game {
public:
	Game();
	~Game();
	Game(Game const &);
	Game &operator=(Game const &);
	bool		init(unsigned lib = 0, int w = 800, int h = 600, int s = 50);
	unsigned	start();

private:
	bool					checkCollision(std::shared_ptr<GameObject>, std::shared_ptr<GameObject>);
	void					addFood();
	void					move();
	void					update();
	void					processCommand();
	std::shared_ptr<DrawAPI>	mApi;
	bool						mIsRunning{true};
	GameState					mState;
	std::shared_ptr<Snake>		mSnake;
	std::shared_ptr<GameLevel>	mLevel;
	int 						mWidth, mHeight, mSize;
	int 						mScore;
	int							mPostAction{-1};
	int							mCurrLib;
	std::unordered_set<std::string> mCommands;
	std::chrono::high_resolution_clock::time_point	mBefore;
};

#endif //NIBBLER_GAME_HPP
