//
// Created by Vadym KOZLOV on 7/7/18.
//

#ifndef NIBBLER_GAME_HPP
#define NIBBLER_GAME_HPP

#include <dlfcn.h>
#include <iostream>
#include "GameLevel.hpp"
#include "Snake.hpp"

typedef void (*initFunction)(int , int , std::string const &);
typedef void (*preFrameFunction)();
typedef void (*drawFunction)(std::array<float, 2> const&);
typedef void (*postFrameFunction)();
typedef const char *(*processInputFunction)(bool &);
typedef void (*deinitFunction)();

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game {
public:
	Game();
	~Game();
	Game(Game const &);
	Game &operator=(Game const &);

	void start();

private:
	bool loadAPI(std::string const &);
private:
	void					processCommand(std::string const &);
	void					*mLib{nullptr};
	initFunction			initApi{nullptr};
	drawFunction			draw{nullptr};
	processInputFunction	getUserInput{nullptr};
	deinitFunction			deinitApi{nullptr};
	preFrameFunction		preFrame{nullptr};
	postFrameFunction		postFrame{nullptr};
	renderFunction			renderer{nullptr};
	bool					mIsRunning{true};
	GameState				mState;
//	std::vector<GameLevel*>	mLevels;
	GameLevel               mLevel;
	Snake*					mSnake;
	int 					mWidth, mHeight;
//	std::chrono::time_point<std::chrono::high_resolution_clock> mBefore;
};

#endif //NIBBLER_GAME_HPP
