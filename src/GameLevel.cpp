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

GameLevel::GameLevel(int width, int height, int size) :
		mLevelWidth(static_cast<size_t>(width)),
		mLevelHeight(static_cast<size_t>(height)),
		mSize(static_cast<size_t>(size))
{
	init();
};

GameLevel::~GameLevel()
{
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

void	GameLevel::addFood(std::shared_ptr<GameObject> aFood)
{
	food.emplace_back(aFood);
}

void GameLevel::init()
{
	std::array<float, 3> color{{0.3f, 0.1f, 0.1f}};
	for (size_t y = 0; y * mSize < mLevelHeight; ++y)
	{
		bricks.emplace_back(std::make_shared<GameObject>(8, 0, y * mSize, mSize, 0, color));
		bricks.emplace_back(std::make_shared<GameObject>(8, mLevelWidth - mSize, y * mSize, mSize, 0, color));
	}
	for (size_t x = 0; x * mSize < mLevelWidth ; ++x)
	{
		bricks.emplace_back(std::make_shared<GameObject>(8, x * mSize, 0, mSize, 0, color));
		bricks.emplace_back(std::make_shared<GameObject>(8, x * mSize, mLevelHeight - mSize, mSize, 0, color));

	}
}