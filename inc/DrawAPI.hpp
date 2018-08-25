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
	DrawAPI(int,int,unsigned);
	~DrawAPI();
	bool 					changeAPI(unsigned);
	processInputFunction	getUserInput{nullptr};
	preFrameFunction		preFrame{nullptr};
	postFrameFunction		postFrame{nullptr};
	renderFunction			drawer{nullptr};
	textFunction			putText{nullptr};
private:
	bool					loadAPI(std::string const &);
	initFunction			initApi{nullptr};
	deinitFunction			deinitApi{nullptr};
	void					*mLib{nullptr};
	DrawAPI(DrawAPI const &);
	DrawAPI &operator=(DrawAPI const &);
	int 						mWidth, mHeight;
	DrawAPI();

	static const std::vector<std::string const> gclibs;
};


#endif //NIBBLER_DRAWAPI_HPP
