//
// Created by Vadym KOZLOV on 8/24/18.
//
#include <dlfcn.h>
#include "DrawAPI.hpp"
#include <iostream>

const std::vector<std::string const> DrawAPI::gclibs{"libSFML.so", "libSDL.so", "libGLFW.so"};

DrawAPI::DrawAPI()
{
};

DrawAPI::DrawAPI(int width, int height, unsigned lib)
{
    std::string name = "Nibbler - " + gclibs[lib % 3];
	loadAPI(gclibs[lib % 3]);
	mAPI = getDisplayModule(width, height, name.c_str());
	if (mAPI == nullptr)
		throw std::exception();
};

const char* DrawAPI::getUserInput(bool &isRunning)
{
    return mAPI->getInput(isRunning);
}

void DrawAPI::preFrame()
{
    mAPI->preFrame();
}
void DrawAPI::postFrame()
{
    mAPI->postFrame();
}
void DrawAPI::drawer(int type, float posX, float posY, float scale, float rot, std::array<float, 3> color)
{
    mAPI->draw(type, posX, posY, scale, rot, color);
}
void DrawAPI::putText(std::string text, float x, float y, float s, std::array<float, 3> color)
{
    mAPI->putText(std::move(text), x, y, s, color);
}

DrawAPI::~DrawAPI()
{
    mAPI->deinitializeApi();
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

void DrawAPI::loadAPI(std::string const &path)
{
	mLib = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!mLib)
	{
		std::cerr << "Error loading the lib: " << std::endl;
		std::cerr << std::string("dlopen : ") + dlerror() << std::endl;
		throw std::exception();
	}
    getDisplayModule = reinterpret_cast<getApiFunction>(dlsym(mLib, "getDisplayModule"));
    if (getDisplayModule == nullptr)
    {
        std::cerr << std::string("dlsym : ") + dlerror() << std::endl;
        throw std::exception();
    }
}
