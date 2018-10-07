/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameLevel.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arxcel <arxcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 21:32:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/09/30 17:13:48 by arxcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMELEVEL_H
# define GAMELEVEL_H

#include <memory>
#include <vector>
#include <string>
#include "GameObject.hpp"

class GameLevel
{
public:
	// Level state
	std::vector< std::shared_ptr<GameObject> > bricks;
	std::vector< std::shared_ptr<GameObject> > food;
	// Constructor
	GameLevel(int width, int heigth, int size, bool hardMod);
	~GameLevel();

	void	addFood(std::shared_ptr<GameObject> aFood);
	// Loads level from file
//	void	load(std::string const & path, int levelWidth, int levelHeight);
    void draw(std::shared_ptr<MediaAPI> const &);
	bool	isCompleted();
private:
	// Initialize level from tile data
    GameLevel();
    GameLevel(GameLevel const &);
    GameLevel &operator=(GameLevel const &);
	void	init();
	size_t	mLevelWidth, mLevelHeight, mSize;
	bool mIsHard;
};

#endif