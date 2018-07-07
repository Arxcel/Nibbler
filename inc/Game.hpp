//
// Created by Vadym KOZLOV on 7/7/18.
//

#ifndef NIBBLER_GAME_HPP
#define NIBBLER_GAME_HPP

#include <dlfcn.h>
#include <iostream>

typedef void (*initFunction)(int width, int height, std::string const winName);

class Game {
public:
	Game();
	~Game();
	Game(Game const &);
	Game &operator=(Game const &);

	void start();

private:
//	void processEvents();
	bool loadAPI(std::string const &);
private:
//	std::vector<AGameObject *> mVertices;
	void			*mLib{nullptr};
	initFunction	initApi{nullptr};
	bool			mIsRunning{true};
//	IAPI			*mDrawer;
//	KeyboardEvent	mKeyPressed;
};

#endif //NIBBLER_GAME_HPP
