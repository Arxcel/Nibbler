//
// Created by Vadym KOZLOV on 8/24/18.
//
#include <dlfcn.h>
#include "DrawAPI.hpp"
#include <vector>
#include <iostream>
std::vector<std::string const> gclibs = {"libSFML.so", "libSDL.so", "libGLFW.so"};

DrawAPI::DrawAPI()
{
};

DrawAPI::DrawAPI(int width, int height, unsigned lib)
{
	if (loadAPI(gclibs[lib % 3]))
		initApi(width, height, "Nibbler - " + gclibs[lib % 3]);
};

DrawAPI::~DrawAPI()
{
	deinitApi();
	if (mLib)
		dlclose(mLib);
};

DrawAPI::DrawAPI(DrawAPI const &)
{
};

DrawAPI &DrawAPI::operator=(DrawAPI const &)
{
	return *this;
};

bool DrawAPI::loadAPI(std::string const &path)
{
	bool result = true;
	if (mLib)
	{
		dlclose(mLib);
	}
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
	result 			&= (initApi != nullptr);
	result 			&= (getUserInput != nullptr);
	result 			&= (deinitApi != nullptr);
	result 			&= (preFrame != nullptr);
	result			&= (postFrame != nullptr);
	result 			&= (drawer != nullptr);
	result 			&= (putText != nullptr);
	if (!result)
		std::cerr << "dlsym : "<< dlerror() << std::endl;
	else
		std::cout << path << " was loaded." << std::endl;
	return result;
}

bool	DrawAPI::changeAPI(unsigned libNum)
{
	deinitApi();
	initApi			= nullptr;
	getUserInput	= nullptr;
	deinitApi		= nullptr;
	preFrame		= nullptr;
	postFrame		= nullptr;
	drawer			= nullptr;
	putText			= nullptr;
	bool result = loadAPI(gclibs[libNum % 3]);
	if (result)
		initApi(mWidth, mHeight, "Nibbler - " + gclibs[libNum % 3]);
	return result;
}