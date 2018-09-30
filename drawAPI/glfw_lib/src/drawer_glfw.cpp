/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer_glfw.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arxcel <arxcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 00:04:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/09/30 17:20:33 by arxcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawer_glfw.hpp"

void Drawer::init(std::string const &winName)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	mWindow = glfwCreateWindow(mWidth, mHeight, winName.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(mWindow);
	if (!gladLoadGL())
		throw CustomException("Failed to initialize GLAD");
	glViewport(0, 0, mWidth * 2, mHeight * 2);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto shader = mRessourceManager.loadShader("drawAPI/shaders/sprite.vx.glsl", "drawAPI/shaders/sprite.ft.glsl", "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(mWidth * 2), static_cast<GLfloat>(mHeight * 2), 0.0f, -1.0f, 1.0f);

	shader->use();
	shader->setInt("image", 0);
	shader->setMat4("projection", projection);
	mSpriteRenderer = std::make_shared<SpriteRenderer>(shader);
	system("pwd");
	mRessourceManager.loadTexture("./drawAPI/asset/snake-1/head.png", "head", true);
	mRessourceManager.loadTexture("./drawAPI/asset/snake-1/body.png", "body", true);
	mRessourceManager.loadTexture("./drawAPI/asset/snake-1/body_turn_left.png", "body_turn_left", true);
	mRessourceManager.loadTexture("./drawAPI/asset/snake-1/body_turn_right.png", "body_turn_right", true);
	mRessourceManager.loadTexture("./drawAPI/asset/snake-1/tail.png", "tail", true);
	mRessourceManager.loadTexture("./drawAPI/asset/food.png", "food", true);

	mRessourceManager.loadTexture("./drawAPI/asset/background.jpg", "background", false);
	mRessourceManager.loadTexture("./drawAPI/asset/block.png", "block", true);

	auto textShader = mRessourceManager.loadShader("drawAPI/shaders/text.vx.glsl", "drawAPI/shaders/text.ft.glsl", "text");

	projection = glm::ortho(0.0f, static_cast<GLfloat>(mWidth), static_cast<GLfloat>(mHeight), 0.0f);


	textShader->use();
	textShader->setInt("text", 0);
	textShader->setMat4("projection", projection);
	mTextRenderer = std::make_shared<TextRenderer>(textShader);
	mTextRenderer->loadFont("./drawAPI/fonts/font.ttf", 24);

	mIsBtnPressed.emplace(GLFW_KEY_W, std::pair<bool, std::string>(false, "UP"));
	mIsBtnPressed.emplace(GLFW_KEY_S, std::pair<bool, std::string>(false, "DOWN"));
	mIsBtnPressed.emplace(GLFW_KEY_A, std::pair<bool, std::string>(false, "LEFT"));
	mIsBtnPressed.emplace(GLFW_KEY_D, std::pair<bool, std::string>(false, "RIGHT"));
	mIsBtnPressed.emplace(GLFW_KEY_MINUS, std::pair<bool, std::string>(false, "Slower"));
	mIsBtnPressed.emplace(GLFW_KEY_EQUAL, std::pair<bool, std::string>(false, "Faster"));
	mIsBtnPressed.emplace(GLFW_KEY_SPACE, std::pair<bool, std::string>(true, "Pause"));
	mIsBtnPressed.emplace(GLFW_KEY_1, std::pair<bool, std::string>(true, "LIB1"));
	mIsBtnPressed.emplace(GLFW_KEY_2, std::pair<bool, std::string>(true, "LIB2"));
	mIsBtnPressed.emplace(GLFW_KEY_3, std::pair<bool, std::string>(true, "LIB3"));
}

std::string Drawer::processKey(int key)
{
	std::string command{"nothing"};
	if (glfwGetKey(mWindow, key) == GLFW_PRESS && !mIsBtnPressed[key].first)
	{
		command = mIsBtnPressed[key].second;
		mIsBtnPressed[key].first = true;
	}
	else if (glfwGetKey(mWindow, key) == GLFW_RELEASE && mIsBtnPressed[key].first)
		mIsBtnPressed[key].first = false;
	return command;
}

std::string Drawer::processInput(bool &isRunning)
{
	std::string command{"nothing"};
	if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, true);
	}
	for (auto &btn : mIsBtnPressed)
	{
		if (command == "nothing")
			command = processKey(btn.first);
	}
	if (glfwWindowShouldClose(mWindow))
		isRunning = false;
	return command;
}

void Drawer::preFrame()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Drawer::postFrame()
{
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

void Drawer::draw(std::string const &tex
		, glm::vec2 const &pos
		, glm::vec2 const &scale
		, float const &rot
		, glm::vec3 const &color)
{
	mSpriteRenderer->drawSprite(mRessourceManager.getTexture(tex), pos, scale, rot, color);
}

void Drawer::putString(std::string const&what, glm::vec2 where, float size, glm::vec3 color)
{
	mTextRenderer->putString(what, where.x, where.y, size, color);
}


void Drawer::deinit()
{
	glfwTerminate();
}



Drawer::Drawer(int width, int height, std::string const &winName)
		: mWidth(width)
		, mHeight(height)

{
	init(winName);
};

Drawer::~Drawer()
{
	std::cout << "glfw finished " << std::endl;
	deinit();
};

Drawer::Drawer(Drawer const &) {};
Drawer &Drawer::operator=(Drawer const &) { return *this; };
