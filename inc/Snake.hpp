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
#include "GameObject.hpp"

enum class Direction {
	UP,
	BOTTOM,
	RIGHT,
	LEFT
};

class Snake {
public:
	Snake(std::array<float, 2>, float, int);
	Snake() = delete;
	~Snake();
	Snake(Snake const &);
	Snake &operator=(Snake const &);
	std::vector<GameObject*> mBody;
	void	draw(renderFunction const &);
	void	move(float dt, int sWidth, int sHeight);

private:
	Direction mCurrentDir;
	bool mStack;
	int mLength;
	float mSize;
};

#endif