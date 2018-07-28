/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameLevel.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 21:32:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/07/16 21:32:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMELEVEL_H
# define GAMELEVEL_H

#include <vector>
#include <string>
#include "GameObject.hpp"

class GameLevel
{
public:
	// Level state
	std::vector<GameObject*> bricks;
	std::vector<GameObject*> food;
	// Constructor
	GameLevel() = delete;
	GameLevel(int width, int heigth, int difficulty, int size);
	~GameLevel();
	GameLevel(GameLevel const &);
	GameLevel &operator=(GameLevel const &);
	void	addFood(GameObject *aFood);
	// Loads level from file
//	void	load(std::string const & path, int levelWidth, int levelHeight);
	void	draw(renderFunction const &);
	bool	isCompleted();
private:
	// Initialize level from tile data
	void	init();
	int		mLevelWidth, mLevelHeight, mDifficulty, mSize;
};

#endif