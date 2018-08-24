/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextRenderer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 23:12:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/08/07 23:12:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <map>

#include "glad/glad.h"
#include <glm/glm.hpp>

#include "Texture.hpp"
#include "Shader.hpp"
#include "Character.hpp"

class TextRenderer
{
public:
	TextRenderer(std::shared_ptr<Shader>);
	~TextRenderer();
	void loadFont(std::string font, GLuint fontSize);
	void putString(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
private:
	std::map<GLchar, std::shared_ptr<Character>> mChars;
	std::shared_ptr<Shader> mTextShader;
	GLuint mVAO, mVBO;
private:
	TextRenderer();
	TextRenderer(TextRenderer const &);
	TextRenderer &operator=(TextRenderer const &);
};

#endif