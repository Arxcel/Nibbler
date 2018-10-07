//
// Created by Vadym KOZLOV on 8/11/18.
//

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class Character {
public:
	Character(FT_Face face);
	~Character();
	GLuint		mTextureID;
	glm::ivec2	mSize;
	glm::ivec2	mBearing;
	GLuint		mAdvance;

private:
	Character(Character const &);
	Character &operator=(Character const&);
	Character();
};


#endif //NIBBLER_CHARACTER_HPP
