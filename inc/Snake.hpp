/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 23:21:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/07/16 23:21:00 by vkozlov          ###   ########.fr       */
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
	Snake() = delete;
	~Snake();
	Snake(Snake const &);
	Snake &operator=(Snake const &);
	std::vector<std::shared_ptr<GameObject>> mBody;
	void	draw(renderFunction const &);
	void	move();
	void	setDirection(Direction d);
	int		&getSpeed();
	void	grow();
private:
	std::array<float, 3> mColor;
	Direction	mCurrentDir;
	Direction	mNextDir;
	size_t		mLength;
	float		mSize;
	int			mSpeed;
};

#endif