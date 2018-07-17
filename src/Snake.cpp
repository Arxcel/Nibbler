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
	std::array<float, 3> color{{0.5f, 0.2f, 0.2f}};
	mBody.emplace_back(new GameObject(3, pos, scale, 180, color));
	for (int i = 1; i < mLength; ++i)
	{
		std::array<float, 2> nPos{{pos[0], pos[1] + size * i}};
		mBody.emplace_back(new GameObject(2, nPos, scale, 180, color));
	}
};

Snake::~Snake() {};
Snake::Snake(Snake const &) {};
Snake &Snake::operator=(Snake const &) { return *this; };

void	Snake::move(float dt, int sWidth, int sHeight)
{
	std::array<float, 2> deltaPos{};
	if (mCurrentDir == Direction::UP)
		deltaPos = {0, -1};
	else if (mCurrentDir == Direction::LEFT)
		deltaPos = {-1, 0};
	else if (mCurrentDir == Direction::RIGHT)
		deltaPos = {1, 0};
	else if (mCurrentDir == Direction::BOTTOM)
		deltaPos = {0, 1};
	std::array<float, 2> prevPos{0, 0};
	std::array<float, 2> currPos{0, 0};
	for (auto &part : mBody)
	{
		currPos = part->mPos;
		if (part->mType == 3)
			;
		else if (part->mType == 2)
			part->mPos = prevPos;
		prevPos = currPos;
	}
	auto head = mBody.at(0);
	head->mPos = {head->mPos[0] + deltaPos[0] * mSize, head->mPos[1] + deltaPos[1] * mSize};
}

void	Snake::draw(renderFunction const &functor)
{
	for (auto &part : mBody)
		part->draw(functor);
}

void Snake::setDirection(Direction d)
{
	if (d == Direction::UP && mCurrentDir != Direction::BOTTOM)
		mCurrentDir = Direction::UP;
	else if (d == Direction::RIGHT && mCurrentDir != Direction::LEFT)
		mCurrentDir = Direction::RIGHT;
	else if (d == Direction::BOTTOM && mCurrentDir != Direction::UP)
		mCurrentDir = Direction::BOTTOM;
	else if (d == Direction::LEFT && mCurrentDir != Direction::RIGHT)
		mCurrentDir = Direction::LEFT;
}