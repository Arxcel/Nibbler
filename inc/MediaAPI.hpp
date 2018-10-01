//
// Created by Vadym KOZLOV on 8/24/18.
//

#ifndef NIBBLER_MediaAPI_HPP
#define NIBBLER_MediaAPI_HPP

#include "MediaAPIFunctions.hpp"
#include <vector>
#include <exception>

class MediaAPI {
public:
	MediaAPI(int, int, unsigned);
	~MediaAPI();
	const char*     getUserInput(bool &);
	void            preFrame();
	void            postFrame();
	void            drawer(int type, float posX, float posY, float scale, float rot, std::array<float, 3> color);
	void            putText(std::string, float, float, float, std::array<float, 3>);
	getDisplayApiFunction  getDisplayModule{nullptr};
	getAudioApiFunction  getAudioModule{nullptr};
	void					playAudio(int type);
	void					stopMusic();
private:
	void            loadAPI(std::string const &);
	void*           mLib{nullptr};
	void*			mAudioLib{nullptr};
	MediaAPI(MediaAPI const &);
	MediaAPI &operator=(MediaAPI const &);
	MediaAPI();
	INibblerDisplay	*mAPI;
	INibblerAudio	*mAudioAPI;
	static const std::vector<std::string const> gclibs;
};


#endif //NIBBLER_MediaAPI_HPP
