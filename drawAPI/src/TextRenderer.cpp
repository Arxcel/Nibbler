/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextRenderer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 23:19:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/08/07 23:19:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "TextRenderer.hpp"

#include <glm/gtc/matrix_transform.hpp>


TextRenderer::TextRenderer(std::shared_ptr<Shader> shader) : mTextShader(shader)
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextRenderer::loadFont(std::string font, GLuint fontSize)
{
	mChars.clear();
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		throw CustomException("ERROR::FREETYPE: Could not init FreeType Library");
	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
		throw CustomException("ERROR::FREETYPE: Failed to load font");
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cerr << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		mChars.emplace(c, std::make_shared<Character>(face));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void TextRenderer::putString(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	mTextShader->use();
	mTextShader->setVec3("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mVAO);
	for (auto &c : text)
	{
		auto ch = mChars[c];
		GLfloat xpos = x + ch->mBearing.x * scale;
		GLfloat ypos = y + (mChars['H']->mBearing.y - ch->mBearing.y) * scale;

		GLfloat w = ch->mSize.x * scale;
		GLfloat h = ch->mSize.y * scale;
		GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 0.0 },
				{ xpos,     ypos,       0.0, 0.0 },

				{ xpos,     ypos + h,   0.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 1.0 },
				{ xpos + w, ypos,       1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch->mTextureID);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (ch->mAdvance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


TextRenderer::~TextRenderer()
{
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
	mChars.clear();
};

TextRenderer::TextRenderer()
{

};
TextRenderer::TextRenderer(TextRenderer const &)
{

};
TextRenderer &TextRenderer::operator=(TextRenderer const &)
{
	return *this;
};