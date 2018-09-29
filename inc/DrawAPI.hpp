//
// Created by Vadym KOZLOV on 8/24/18.
//

#ifndef NIBBLER_DRAWAPI_HPP
#define NIBBLER_DRAWAPI_HPP

#include "DrawAPIFunctions.hpp"
#include <vector>
#include <exception>

class DrawAPI {
public:
	DrawAPI(int, int, unsigned);
	~DrawAPI();
	const char*     getUserInput(bool &);
	void            preFrame();
	void            postFrame();
	void            drawer(int type, float posX, float posY, float scale, float rot, std::array<float, 3> color);
	void            putText(std::string, float, float, float, std::array<float, 3>);
	getApiFunction  getDisplayModule{nullptr};
private:
	void            loadAPI(std::string const &);
	void*           mLib{nullptr};
	DrawAPI(DrawAPI const &);
	DrawAPI &operator=(DrawAPI const &);
	DrawAPI();
	INibblerDisplay	*mAPI;
	static const std::vector<std::string const> gclibs;
};


#endif //NIBBLER_DRAWAPI_HPP
