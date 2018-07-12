//
// Created by Vadym KOZLOV on 7/7/18.
//

#ifndef NIBBLER_GAME_HPP
#define NIBBLER_GAME_HPP

#include <dlfcn.h>
#include <iostream>

typedef void (*initFunction)(int , int , std::string const &);
typedef void (*preFrameFunction)();
typedef void (*drawFunction)(int,int,int);
typedef void (*postFrameFunction)();
typedef int (*processInputFunction)(bool &);
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
	void					*mLib{nullptr};
	initFunction			initApi{nullptr};
	drawFunction			draw{nullptr};
	processInputFunction	getUserInput{nullptr};
	deinitFunction			deinitApi{nullptr};
	preFrameFunction		preFrame{nullptr};
	postFrameFunction		postFrame{nullptr};
	bool					mIsRunning{true};
};

#endif //NIBBLER_GAME_HPP
