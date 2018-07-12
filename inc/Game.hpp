//
// Created by Vadym KOZLOV on 7/7/18.
//

#ifndef NIBBLER_GAME_HPP
#define NIBBLER_GAME_HPP

#include <dlfcn.h>
#include <iostream>

typedef void (*initFunction)(int width, int height, std::string const winName);
typedef void (*drawFunction)();
typedef void (*processInputFunction)(bool &);
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
	bool					mIsRunning{true};
};

#endif //NIBBLER_GAME_HPP
