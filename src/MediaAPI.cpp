//
// Created by Vadym KOZLOV on 8/24/18.
//
#include <dlfcn.h>
#include "MediaAPI.hpp"
#include <iostream>

const std::vector<std::string const> MediaAPI::gclibs{"libSFML.so", "libSDL.so", "libGLFW.so"};

MediaAPI::MediaAPI()
{
};

MediaAPI::MediaAPI(int width, int height, unsigned lib)
{
    std::string name = "Nibbler - " + gclibs[lib % 3];
	loadAPI(gclibs[lib % 3]);
	mAPI = getDisplayModule(width, height, name.c_str());
	mAudioAPI = getAudioModule();
	if (mAPI == nullptr || mAudioAPI == nullptr)
		throw std::exception();
	mAudioAPI->startMain();
};

const char* MediaAPI::getUserInput(bool &isRunning)
{
    return mAPI->getInput(isRunning);
}

void MediaAPI::playAudio(int type)
{
	mAudioAPI->playSound(type);
}

void MediaAPI::stopMusic()
{
	mAudioAPI->stopMain();
	mAudioAPI->playSound(2);
}

void MediaAPI::preFrame()
{
    mAPI->preFrame();
}
void MediaAPI::postFrame()
{
    mAPI->postFrame();
}
void MediaAPI::drawer(int type, float posX, float posY, float scale, float rot, std::array<float, 3> color)
{
    mAPI->draw(type, posX, posY, scale, rot, color);
}
void MediaAPI::putText(std::string text, float x, float y, float s, std::array<float, 3> color)
{
    mAPI->putText(std::move(text), x, y, s, color);
}

MediaAPI::~MediaAPI()
{
    mAPI->deinitializeApi();
	if (mLib)
		dlclose(mLib);
};

MediaAPI::MediaAPI(MediaAPI const &)
{
};

MediaAPI &MediaAPI::operator=(MediaAPI const &)
{
	return *this;
};

void MediaAPI::loadAPI(std::string const &path)
{
	mLib = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!mLib)
	{
		std::cerr << "Error loading the lib: " << std::endl;
		std::cerr << std::string("dlopen : ") + dlerror() << std::endl;
		throw std::exception();
	}
    getDisplayModule = reinterpret_cast<getDisplayApiFunction>(dlsym(mLib, "getDisplayModule"));
    if (getDisplayModule == nullptr)
    {
        std::cerr << std::string("dlsym : ") + dlerror() << std::endl;
        throw std::exception();
    }

	mAudioLib = dlopen("libAudio.so", RTLD_LAZY | RTLD_LOCAL);
	if (!mAudioLib)
	{
		std::cerr << "Error loading the lib: " << std::endl;
		std::cerr << std::string("dlopen : ") + dlerror() << std::endl;
		throw std::exception();
	}

    getAudioModule = reinterpret_cast<getAudioApiFunction>(dlsym(mAudioLib, "getAudioModule"));
    if (getAudioModule == nullptr)
    {
        std::cerr << std::string("dlsym : ") + dlerror() << std::endl;
        throw std::exception();
    }
}
