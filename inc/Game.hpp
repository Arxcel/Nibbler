//
// Created by Vadym KOZLOV on 7/7/18.
//

#ifndef NIBBLER_GAME_HPP
#define NIBBLER_GAME_HPP

#include <dlfcn.h>
#include <iostream>
#include <chrono>
#include "GameLevel.hpp"
#include "Snake.hpp"

typedef void		(*initFunction)(int , int , std::string const &);
typedef void		(*preFrameFunction)();
typedef void		(*postFrameFunction)();
typedef const char*	(*processInputFunction)(bool &);
typedef void		(*deinitFunction)();

enum GameState {
	GAME_ACTIVE,
	GAME_MENU
};

class Game {
public:
	Game();
	~Game();
	Game(Game const &);
	Game &operator=(Game const &);

	void					start();

private:
	bool					loadAPI(std::string const &);
private:
	bool					checkCollision(GameObject *, GameObject *);
	void					addFood();
	void					move();
	void					update();
	void					processCommand(std::string const &);
	void					*mLib{nullptr};
	initFunction			initApi{nullptr};
	processInputFunction	getUserInput{nullptr};
	deinitFunction			deinitApi{nullptr};
	preFrameFunction		preFrame{nullptr};
	postFrameFunction		postFrame{nullptr};
	renderFunction			renderer{nullptr};
	bool					mIsRunning{true};
	GameState				mState;
	Snake*					mSnake;
	GameLevel*				mLevel;
	int 					mWidth, mHeight, mSize;
	std::chrono::high_resolution_clock::time_point	mBefore;
};

#endif //NIBBLER_GAME_HPP
