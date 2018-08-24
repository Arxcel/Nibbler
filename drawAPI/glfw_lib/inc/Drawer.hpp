/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Drawer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 00:03:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/07/08 00:03:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef DRAWER_H
# define DRAWER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "CustomException.hpp"
#include "ResourceManager.hpp"
#include "SpriteRenderer.hpp"
#include "TextRenderer.hpp"
#include <map>

class Drawer {
public:
	Drawer(int width, int height, std::string const &winName);
	~Drawer();
	std::string		processInput(bool &);
	void			preFrame();
	void			postFrame();
	void			draw(std::string const &texture, glm::vec2 const &pos, glm::vec2 const &scale, float const &rot = 0.0f, glm::vec3 const &color = glm::vec3(1.0f));
	void			putString(std::string const&what,glm::vec2 where, float size, glm::vec3 color);
private:
	int								mWidth, mHeight;
	std::shared_ptr<SpriteRenderer>	mSpriteRenderer;
	std::shared_ptr<TextRenderer>	mTextRenderer;
	ResourceManager					mRessourceManager;
	GLFWwindow*						mWindow;
private:
	std::string		processKey(int key);
	void			init(int width, int height, std::string const &winName);
	void			deinit();
	Drawer(Drawer const &);
	Drawer &operator=(Drawer const &);
	std::map<int , std::pair<bool, std::string> > mIsBtnPressed;
};

#endif