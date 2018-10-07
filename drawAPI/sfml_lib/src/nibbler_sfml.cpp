//
// Created by Vadym KOZLOV on 7/7/18.
//
#include <vector>
#include "nibbler_sfml.hpp"

const std::vector<std::string> cTextures{ "block", "head", "body", "body_turn_left", "body_turn_right", "tail", "food"};

extern "C" INibblerDisplay*			getDisplayModule(int width, int height, const char *winName)
{
	return new NibblerDisplaySFML(width, height, winName);
}

NibblerDisplaySFML::NibblerDisplaySFML(int width, int height, const char *winName): mDrawer(width, height, winName)
{
}

void NibblerDisplaySFML::preFrame()
{
	mDrawer.preFrame();
}

void NibblerDisplaySFML::postFrame()
{
	mDrawer.postFrame();
}

const char *NibblerDisplaySFML::getInput(bool &isRunning)
{
	std::string cmd = mDrawer.processInput(isRunning);
	if (cmd != "nothing")
		return cmd.c_str();
	return nullptr;
}

void NibblerDisplaySFML::deinitializeApi()
{
	delete this;
}

void NibblerDisplaySFML::draw(int type
		, float posX, float posY
		, float scale
		, float rot
		, std::array<float, 3> color)
{
    if (static_cast<size_t>(type) > cTextures.size())
        type = 0;
	mDrawer.draw(cTextures[type], {posX, posY}, {scale, scale}, static_cast<float>(rot * M_PI / 180.0f), {color[0], 0, color[2]});
}

void			NibblerDisplaySFML::putText(std::string what, float x, float y, float size, std::array<float, 3> color)
{
	mDrawer.putString(what, {x, y}, size, {color[0], color[1], color[2]});
}

NibblerDisplaySFML::~NibblerDisplaySFML()
{
}
NibblerDisplaySFML::NibblerDisplaySFML(): mDrawer(100, 100, "no name")
{
}
NibblerDisplaySFML::NibblerDisplaySFML(NibblerDisplaySFML const &): mDrawer(100, 100, "no name")
{
}
NibblerDisplaySFML &NibblerDisplaySFML::operator=(NibblerDisplaySFML const &)
{
	return *this;
}
