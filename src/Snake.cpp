/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 23:21:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/07/16 23:21:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"

Snake::Snake(std::array<float, 2> pos, float size, int length) : mCurrentDir(Direction::UP), mStack(true), mLength(length), mSize(size)
{
	std::array<float, 2> scale{{size, size}};
	std::array<float, 3> color{{1.0f, 1.0f, 1.0f}};
	mBody.emplace_back(new GameObject(3, pos[0], pos[1], size, 0, color));
	for (int i = 1; i < mLength; ++i)
	{
		std::array<float, 2> nPos{{pos[0], pos[1] + size * i}};
		mBody.emplace_back(new GameObject(2, nPos[0], nPos[1], size, 0, color));
	}
};

Snake::~Snake()
{
	for (auto &part : mBody)
		delete part;
};
Snake::Snake(Snake const &) {};
Snake &Snake::operator=(Snake const &) { return *this; };

void	Snake::move()
{
	float deltaX = 0, deltaY = 0, deltaAngle = 0;
	if (mCurrentDir == Direction::UP)
		deltaY = -1;
	else if (mCurrentDir == Direction::LEFT)
	{
		deltaX = -1;
		deltaAngle = -90;
	}
	else if (mCurrentDir == Direction::RIGHT)
	{
		deltaX = 1;
		deltaAngle = 90;
	}
	else if (mCurrentDir == Direction::BOTTOM)
	{
		deltaY = 1;
		deltaAngle = 180;
	}
	float prevX{0}, prevY{0}, currX{0}, currY{0};
	for (auto &part : mBody)
	{
		currX = part->mPosX;
		currY = part->mPosY;
		if(part->mType == 3)
		{
			part->mRotation = deltaAngle;
			part->mPosX += deltaX * mSize;
			part->mPosY += deltaY * mSize;
		}
		else
		{
			part->mPosX = prevX;
			part->mPosY = prevY;
		}
		prevX = currX;
		prevY = currY;
	}
}

void	Snake::draw(renderFunction const &functor)
{
	for (auto &part : mBody)
		part->draw(functor);
}

void Snake::setDirection(Direction d)
{
	mCurrentDir = d;
}