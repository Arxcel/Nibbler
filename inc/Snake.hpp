/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arxcel <arxcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 23:21:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/09/30 17:13:48 by arxcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_H
# define SNAKE_H

#include <vector>
#include <string>
#include <memory>
#include "GameObject.hpp"

enum class Direction {
	UP		= 0,
	BOTTOM	= 1,
	RIGHT	= 2,
	LEFT	= 3
};

class Snake {
public:
	Snake(std::array<float, 2>, float, int);
	~Snake();
	Snake(Snake const &);
	Snake &operator=(Snake const &);
	std::vector<std::shared_ptr<GameObject>> mBody;
	void	draw(std::shared_ptr<MediaAPI> const &api);
	void	move();
	void	setDirection(Direction d);
	int		&getSpeed();
	void	grow();
private:
	Snake();
	std::array<float, 3> mColor;
	Direction	mCurrentDir;
	Direction	mNextDir;
	size_t		mLength;
	float		mSize;
	int			mSpeed;
};

#endif