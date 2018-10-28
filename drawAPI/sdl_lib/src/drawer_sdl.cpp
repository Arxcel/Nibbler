/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer_sdl.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 00:04:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/10/28 13:13:26 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawer_sdl.hpp"

void Drawer::init(int width, int height, std::string const &winName)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	int context_flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	mWindow = SDL_CreateWindow(winName.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	mContext = SDL_GL_CreateContext(mWindow);
	SDL_GL_MakeCurrent(mWindow, mContext);
	// if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	if (!gladLoadGL())
		throw CustomException("Failed to initialize GLAD");
	glViewport(0, 0, width, height);
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

	mIsBtnPressed.emplace(SDLK_w, "UP");
	mIsBtnPressed.emplace(SDLK_s, "DOWN");
	mIsBtnPressed.emplace(SDLK_a, "LEFT");
	mIsBtnPressed.emplace(SDLK_d, "RIGHT");
	mIsBtnPressed.emplace(SDLK_UP, "UP");
	mIsBtnPressed.emplace(SDLK_DOWN, "DOWN");
	mIsBtnPressed.emplace(SDLK_LEFT, "LEFT");
	mIsBtnPressed.emplace(SDLK_RIGHT, "RIGHT");
	mIsBtnPressed.emplace(SDLK_MINUS, "Slower");
	mIsBtnPressed.emplace(SDLK_EQUALS, "Faster");
	mIsBtnPressed.emplace(SDLK_SPACE, "Pause");
	mIsBtnPressed.emplace(SDLK_1, "LIB1");
	mIsBtnPressed.emplace(SDLK_2, "LIB2");
	mIsBtnPressed.emplace(SDLK_3, "LIB3");

}

std::string Drawer::processInput(bool &isRunning)
{
	std::string command{"nothing"};
	if (mE.type == SDL_KEYDOWN)
	{
		auto find = mIsBtnPressed.find(mE.key.keysym.sym);
		if	(find != mIsBtnPressed.end())
			command = find->second;
	}
	if(mE.type == SDL_QUIT || (mE.type == SDL_KEYDOWN && mE.key.keysym.sym == SDLK_ESCAPE))
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
	SDL_GL_SwapWindow(mWindow);
	SDL_PollEvent(&mE);
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
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}



Drawer::Drawer(int width, int height, std::string const &winName)
		: mWidth(width)
		, mHeight(height)

{
	init(width, height, winName);
};

Drawer::~Drawer()
{
	deinit();
};

Drawer::Drawer(Drawer const &) {};
Drawer &Drawer::operator=(Drawer const &) { return *this; };
