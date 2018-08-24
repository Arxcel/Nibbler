/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Drawer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 00:04:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/08/24 16:15:05 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Drawer.hpp"

void Drawer::init(int width, int height, std::string const &winName)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	mWindow.create(sf::VideoMode(width * 2, height * 2), winName, sf::Style::Close, settings);
	if (!gladLoadGL())
		throw CustomException("Failed to initialize GLAD");
	glViewport(0, 0, width * 2, height * 2);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto shader = mRessourceManager.loadShader("drawAPI/shaders/sprite.vx.glsl", "drawAPI/shaders/sprite.ft.glsl", "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width * 2), static_cast<GLfloat>(height * 2), 0.0f, -1.0f, 1.0f);

	shader->use();
	shader->setInt("image", 0);
	shader->setMat4("projection", projection);
	mSpriteRenderer = std::make_shared<SpriteRenderer>(shader);
	mRessourceManager.loadTexture("./drawAPI/asset/snake-2/head.png", "head", true);
	mRessourceManager.loadTexture("./drawAPI/asset/snake-2/body.png", "body", true);
	mRessourceManager.loadTexture("./drawAPI/asset/snake-2/body_turn_left.png", "body_turn_left", true);
	mRessourceManager.loadTexture("./drawAPI/asset/snake-2/body_turn_right.png", "body_turn_right", true);
	mRessourceManager.loadTexture("./drawAPI/asset/snake-2/tail.png", "tail", true);
	mRessourceManager.loadTexture("./drawAPI/asset/food3.png", "food", true);

	mRessourceManager.loadTexture("./drawAPI/asset/background.jpg", "background", false);
	mRessourceManager.loadTexture("./drawAPI/asset/block2.png", "block", false);

	auto textShader = mRessourceManager.loadShader("drawAPI/shaders/text.vx.glsl", "drawAPI/shaders/text.ft.glsl", "text");

	projection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f);


	textShader->use();
	textShader->setInt("text", 0);
	textShader->setMat4("projection", projection);
	mTextRenderer = std::make_shared<TextRenderer>(textShader);
	mTextRenderer->loadFont("./drawAPI/fonts/font.ttf", 24);

	mIsBtnPressed.emplace(sf::Keyboard::W, "UP");
	mIsBtnPressed.emplace(sf::Keyboard::S, "DOWN");
	mIsBtnPressed.emplace(sf::Keyboard::A, "LEFT");
	mIsBtnPressed.emplace(sf::Keyboard::D, "RIGHT");
	mIsBtnPressed.emplace(sf::Keyboard::Subtract, "Slower");
	mIsBtnPressed.emplace(sf::Keyboard::Equal, "Faster");
	mIsBtnPressed.emplace(sf::Keyboard::Space, "Pause");
	mIsBtnPressed.emplace(sf::Keyboard::Num1, "LIB1");
	mIsBtnPressed.emplace(sf::Keyboard::Num2, "LIB2");
	mIsBtnPressed.emplace(sf::Keyboard::Num3, "LIB3");
}

std::string Drawer::processInput(bool &isRunning)
{
	std::string command{"nothing"};
	if (mE.type == sf::Event::KeyPressed)
	{
		auto find = mIsBtnPressed.find(mE.key.code);
		if	(find != mIsBtnPressed.end())
			command = find->second;
		if(mE.key.code == sf::Keyboard::Escape)
			isRunning = false;
	}
	// else if(mE.type == sf::Event::Closed)
		// isRunning = false;
	return command;
}

void Drawer::preFrame()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Drawer::postFrame()
{
	mWindow.display();
	mWindow.pollEvent(mE);
}

void Drawer::draw(std::string const &tex
		, glm::vec2 const &pos
		, glm::vec2 const &scale
		, float const &rot
		, glm::vec3 const &color)
{
	mSpriteRenderer->drawSprite(mRessourceManager.getTexture(tex) , pos, scale, rot, color);
}

void Drawer::putString(std::string const&what,glm::vec2 where, float size, glm::vec3 color)
{
	mTextRenderer->putString(what, where.x, where.y, size, color);
}


void Drawer::deinit()
{
	mWindow.close();
}



Drawer::Drawer(int width, int height, std::string const &winName)
		: mWidth(width)
		, mHeight(height)

{
	init(width, height, winName);
};

Drawer::~Drawer()
{
	std::cout << "sfml finished " << std::endl;
	deinit();
};

Drawer::Drawer(Drawer const &) {};
Drawer &Drawer::operator=(Drawer const &) { return *this; };
