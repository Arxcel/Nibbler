//
// Created by Vadym KOZLOV on 9/29/18.
//

#include <array>

#ifndef NIBBLER_GAME_INIBBLERDISPLAY_H
#define NIBBLER_GAME_INIBBLERDISPLAY_H

//extern "C" void			initializeApi(int width, int height, std::string const &winName);
//extern "C" const char	*getInput(bool &);
//extern "C" void			deinitializeApi();
//extern "C" void			draw(int
//        , float
//        , float
//        , float
//        , float
//        , std::array<float, 3>);
//extern "C" void			putText(std::string what, float x, float y, float size, std::array<float, 3>);

class INibblerDisplay
{
public:
    virtual ~INibblerDisplay() {};
    virtual void preFrame() = 0;
    virtual void postFrame() = 0;
    virtual void			draw(int
                        , float
                        , float
                        , float
                        , float
                        , std::array<float, 3>) = 0;
    virtual void			putText(std::string what, float x, float y, float size, std::array<float, 3>) = 0;
    virtual void			deinitializeApi() = 0;
    virtual const char	*getInput(bool &) = 0;

};

#endif //NIBBLER_GAME_INIBBLERDISPLAY_H
