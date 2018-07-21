/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameLevel.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 21:32:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/07/16 21:32:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fstream>
#include <sstream>
#include <iostream>
#include "GameLevel.hpp"

//GameLevel::GameLevel() {};
GameLevel::GameLevel(int width, int height, int size, int difficulty) : mLevelWidth(width), mLevelHeight(height), mDifficulty(difficulty), mSize(size)
{
	init();
};

GameLevel::~GameLevel()
{
	for (auto &brick : bricks)
		delete brick;
	for (auto &f : food)
		delete f;
};

GameLevel::GameLevel(GameLevel const &) {};

GameLevel &GameLevel::operator=(GameLevel const &) { return *this; };

void	GameLevel::draw(renderFunction const &functor)
{
	for (auto &brick : bricks)
		brick->draw(functor);
	for (auto &f : food)
		f->draw(functor);
}

bool	GameLevel::isCompleted()
{
	return false;
}

void	GameLevel::addFood(int x, int y)
{
	std::array<float, 3> color{{1.0f, 1.0f, 1.0f}};
	food.emplace_back(new GameObject(6, x * mSize, y * mSize, mSize, 180, color));
//	std::cout << x << std::endl;
//	std::cout << y << std::endl;
}

void GameLevel::init()
{
	std::array<float, 3> color{{0.3f, 0.1f, 0.1f}};
	for (size_t y = 0; y * mSize < mLevelHeight; ++y)
	{
		bricks.emplace_back(new GameObject(8, 0, y * mSize, mSize, 0, color));
		bricks.emplace_back(new GameObject(8, mLevelWidth - mSize, y * mSize, mSize, 0, color));
	}
	for (size_t x = 0; x * mSize < mLevelWidth ; ++x)
	{
		bricks.emplace_back(new GameObject(8, x * mSize, 0, mSize, 0, color));
		bricks.emplace_back(new GameObject(8, x * mSize, mLevelHeight - mSize, mSize, 0, color));

	}
}