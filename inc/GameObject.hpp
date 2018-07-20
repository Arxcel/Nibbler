/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 21:07:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/07/16 21:07:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef NIBBLER_GAMEOBJECT_HPP
#define NIBBLER_GAMEOBJECT_HPP
#include <array>

typedef void (*renderFunction)(int type
		, float posX, float posY
		, float scale
		, float rot
		, std::array<float, 3> color);

class GameObject
{
public:
	~GameObject();
	GameObject() = delete;
	GameObject(int, float, float, float, float, std::array<float, 3>);
	GameObject(GameObject const &);
	GameObject &operator=(GameObject const &);

	// Object state
	int						mType;
	float 					x;
	float					y;
	float 					mSize;
	float					mRotation;
	std::array<float, 3>	mColor;
	// Draw sprite
	virtual void draw(renderFunction const &);
};
#endif //NIBBLER_GAMEOBJECT_HPP
