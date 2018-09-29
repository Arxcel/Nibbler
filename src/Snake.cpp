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

Snake::Snake(std::array<float, 2> pos, float size, int length) : mColor({{1.0f, 1.0f, 1.0f}}),
																 mCurrentDir(Direction::UP),
																 mNextDir(Direction::UP),
																 mLength(static_cast<size_t>(length)),
																 mSize(size),
																 mSpeed(5)
{
	mBody.emplace_back(std::make_shared<GameObject>(1, pos[0], pos[1], size, 0, mColor));
	for (size_t i = 1; i < mLength; ++i)
		mBody.emplace_back(std::make_shared<GameObject>(2, pos[0], pos[1] + size * i, size, 0 , mColor));
	mBody.emplace_back(std::make_shared<GameObject>(5, pos[0], pos[1] + size * (mLength), size, 0, mColor));
};

Snake::~Snake()
{
};


void	Snake::grow()
{
	mLength++;
	mBody.emplace_back(std::make_shared<GameObject>(2, -100, -100, mSize, 0 , mColor));
}

Snake::Snake(Snake const &) {};
Snake &Snake::operator=(Snake const &) { return *this; };

void	Snake::move() {
	mCurrentDir = mNextDir;
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
			part->mType = 5;
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
			auto prev = mBody.at(i);
			auto next = mBody.at(i + 1);

			float dirX, dirY;
			float tmpNextX, tmpNextY;
			tmpNextX = (prev->x - next->x) / mSize;
			tmpNextY = (prev->y - next->y) / mSize;
			if (i != 0)
			{
				dirX = (currX - prev->x) / mSize;
				dirY = (currY - prev->y) / mSize;
			}
			else
			{
				dirX = deltaX == 0 ? 0 : -deltaX;
				dirY = deltaY == 0 ? 0 : -deltaY;
			}
			if ((tmpNextX == -1		&& tmpNextY == -1	&& dirX == 1	&& dirY == 0)	||
					(tmpNextX == -1	&& tmpNextY == 1	&& dirX == 0	&& dirY == -1)	||
					(tmpNextX == 1	&& tmpNextY == 1	&& dirX == -1	&& dirY == 0)	||
					(tmpNextX == 1	&& tmpNextY == -1	&& dirX == 0	&& dirY == 1))
				next->mType = 3;
			else if ((tmpNextX == -1	&& tmpNextY == -1	&& dirX == 0	&& dirY == 1)	||
					(tmpNextX == 1		&& tmpNextY == -1	&& dirX == -1	&& dirY == 0)	||
					(tmpNextX == 1		&& tmpNextY == 1	&& dirX == 0	&& dirY == -1)	||
					(tmpNextX == -1		&& tmpNextY == 1	&& dirX == 1	&& dirY == 0))
				next->mType = 4;
			else
				next->mType = 2;
		}
	}
}

void	Snake::draw(std::shared_ptr<DrawAPI> const &api)
{
	for (auto &part : mBody)
		part->draw(api);
}

void Snake::setDirection(Direction d)
{
	if ((mCurrentDir == Direction::UP && d == Direction::BOTTOM)		||
			(mCurrentDir == Direction::BOTTOM && d == Direction::UP)	||
			(mCurrentDir == Direction::RIGHT && d == Direction::LEFT)	||
			(mCurrentDir == Direction::LEFT && d == Direction::RIGHT))
		return;
	mNextDir = d;
}

int &Snake::getSpeed()
{
	return mSpeed;
}