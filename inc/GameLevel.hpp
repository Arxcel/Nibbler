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
	// Constructor
	GameLevel();
	~GameLevel();
	GameLevel(GameLevel const &);
	GameLevel &operator=(GameLevel const &);
	// Loads level from file
	void	load(std::string const & path, int levelWidth, int levelHeight);
	void	draw(renderFunction const &);
	bool	isCompleted();
private:
	// Initialize level from tile data
	void	init(std::vector<std::vector<int>> tileData, int levelWidth, int levelHeight);
};

#endif