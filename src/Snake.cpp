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
#include <iostream>

Snake::Snake(std::array<float, 2> pos, float size, int length) : mCurrentDir(Direction::UP), mStack(true), mLength(length), mSize(size)
{
	std::array<float, 2> scale{{size, size}};
	std::array<float, 3> color{{1.0f, 1.0f, 1.0f}};
	mBody.emplace_back(new GameObject(1, pos[0], pos[1], size, 0, color));
	for (int i = 1; i < mLength; ++i)
	{
		std::array<float, 2> nPos{{pos[0], pos[1] + size * i}};
		mBody.emplace_back(new GameObject(2, nPos[0], nPos[1], size, 0 , color));
	}
	std::array<float, 2> nPos{{pos[0], pos[1] + size * (mLength)}};
	mBody.emplace_back(new GameObject(4, nPos[0], nPos[1], size, 0, color));
};

Snake::~Snake()
{
	for (auto &part : mBody)
		delete part;
};
Snake::Snake(Snake const &) {};
Snake &Snake::operator=(Snake const &) { return *this; };

void	Snake::move() {
	float deltaX = 0, deltaY = 0, deltaAngle = 0;
	if (mCurrentDir == Direction::UP)
		deltaY = -1;
	else if (mCurrentDir == Direction::LEFT) {
		deltaX = -1;
		deltaAngle = -90;
	} else if (mCurrentDir == Direction::RIGHT) {
		deltaX = 1;
		deltaAngle = 90;
	} else if (mCurrentDir == Direction::BOTTOM) {
		deltaY = 1;
		deltaAngle = 180;
	}
	float prevX{0}, prevY{0}, prevA{0};
	float currX{0}, currY{0}, currA{0};
	float nextX{0}, nextY{0}, nextA{0};
	bool turn;
	for (size_t i = 0; i <= mLength; ++i)
	{
		auto part = mBody.at(i);
		if (i == 0) // HEAD
		{
			prevX = part->x;
			prevY = part->y;
			prevA = part->mRotation;
			part->x += deltaX * mSize;
			part->y += deltaY * mSize;
			part->mType = 1;
			part->mRotation = deltaAngle;
		}
		else if (i == mLength) //TAIL
		{
			part->x = prevX;
			part->y = prevY;
			part->mRotation = mBody.at(i - 1)->mRotation;
			part->mType = 4;
		}
		else
		{
			currX = part->x;
			currY = part->y;
			currA = part->mRotation;
			part->x = prevX;
			part->y = prevY;
			part->mRotation = prevA;
			prevX = currX;
			prevY = currY;
			prevA = currA;
		}

		if (i < mLength)
		{
			auto curr = mBody.at(i);
			auto next = mBody.at(i + 1);

			float tmpNextX, tmpNextY;
			tmpNextX = (curr->x - next->x) / mSize;
			tmpNextY = (curr->y - next->y) / mSize;
			if (tmpNextX != 0 && tmpNextY != 0)
				std::cout << tmpNextX << " " << tmpNextY << std::endl << std::endl;
			if (tmpNextX != 0 && tmpNextY != 0)
				next->mType = 3;
			else
				next->mType = 2;
		}
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