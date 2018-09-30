/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameLevel.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arxcel <arxcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 21:32:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/09/30 17:13:48 by arxcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <iostream>
#include "GameLevel.hpp"

GameLevel::GameLevel(int width, int height, int size, bool hardMod) :
		mLevelWidth(static_cast<size_t>(width)),
		mLevelHeight(static_cast<size_t>(height)),
		mSize(static_cast<size_t>(size))
{
	mIsHard = hardMod;
	init();
};

GameLevel::~GameLevel()
{
};

GameLevel::GameLevel(GameLevel const &) {};

GameLevel &GameLevel::operator=(GameLevel const &) { return *this; };

void GameLevel::draw(std::shared_ptr<MediaAPI> const &api)
{
	for (auto &brick : bricks)
		brick->draw(api);
	for (auto &f : food)
		f->draw(api);
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
		for (size_t x = 0; x * mSize <= mLevelWidth; ++x)
		{
            if ((x == 0 || x == mLevelWidth / mSize - 1 || y == 0 || y == mLevelHeight / mSize - 1) || (x % 2 != 0 && y % 2 != 0 && mIsHard))
			{
				bricks.emplace_back(std::make_shared<GameObject>(8, x * mSize, y * mSize, mSize, 0, color));
			}
		}
	}

}