//
// Created by Vadym KOZLOV on 7/7/18.
//
#include "nibbler_sdl.hpp"

std::shared_ptr<Drawer> gD;

extern "C" void initializeApi(int width, int height, std::string const &winName)
{
	gD = std::make_shared<Drawer>(width, height, winName);
}

extern "C" void preFrame()
{
	gD->preFrame();
}

extern "C" void postFrame()
{
	gD->postFrame();
}

extern "C" const char *getInput(bool &isRunning)
{
	std::string cmd = gD->processInput(isRunning);
	if (cmd != "nothing")
		return cmd.c_str();
	return nullptr;
}

extern "C" void deinitializeApi()
{
	gD.reset();
}

extern "C" void draw(int type
		, float posX, float posY
		, float scale
		, float rot
		, std::array<float, 3> color)
{
	std::string texture;
	switch (type)
	{
		case 1:
			texture = "head";
			break;
		case 2:
			texture = "body";
			break;
		case 3:
			texture = "body_turn_left";
			break;
		case 4:
			texture = "body_turn_right";
			break;
		case 5:
			texture = "tail";
			break;
		case 6:
			texture = "food";
			break;
		default:
			texture = "block";
	}
	gD->draw(texture, {posX, posY}, {scale, scale}, static_cast<float>(rot * M_PI / 180.0f), {color[0], color[1], color[2]});
}

extern "C" void			putText(std::string what, float x, float y, float size, std::array<float, 3> color)
{
	gD->putString(what, {x, y}, size, {color[0], color[1], color[2]});
}