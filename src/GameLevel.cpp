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

GameLevel::GameLevel() {};

GameLevel::~GameLevel() {};

GameLevel::GameLevel(GameLevel const &) {};

GameLevel &GameLevel::operator=(GameLevel const &) { return *this; };


void	GameLevel::load(std::string const & path, int levelWidth, int levelHeight)
{
	bricks.clear();
	std::cout << path << std::endl;
	int tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(path);
	std::vector<std::vector<int >> tileData;
	if (fstream)
	{
		int i = 0;
		while (std::getline(fstream, line))
		{
			i++;
			std::istringstream sstream(line);
			std::vector<int > row;
			while (sstream >> tileCode)
			{
				row.push_back(tileCode);
				std::cout << tileCode << " ";
			}
			tileData.push_back(row);
			std::cout << std::endl;
		}
		if (!tileData.empty())
			this->init(tileData, levelWidth, levelHeight);
	}
}

void	GameLevel::draw(renderFunction const &functor)
{
	for (auto &brick : bricks)
		brick->draw(functor);
}

bool	GameLevel::isCompleted()
{
	return false;
}

void GameLevel::init(std::vector<std::vector<int>> tileData, int levelWidth, int levelHeight)
{
//	size_t height = tileData.size();
//	size_t width = tileData[0].size();
//	float	unitWidth = levelWidth / static_cast<float>(width),
//			unitHeight = levelHeight / static_cast<float>(height);
//	for (size_t y = 0; y < height; ++y)
//	{
//		for (size_t x = 0; x < width; ++x)
//		{
//			if (tileData[y][x] > 0)
//			{
//				std::array<float, 2> pos{{unitWidth * x, unitHeight * y}};
//				std::array<float, 2> scale{{unitWidth, unitHeight}};
//				std::array<float, 3> color{{0.8f, 0.8f, 0.7f}};
//				bricks.emplace_back(new GameObject(1, pos, scale, 0, color));
//			}
//		}
//	}
}