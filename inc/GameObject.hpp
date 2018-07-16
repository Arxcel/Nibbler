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

typedef void (*renderFunction)(int const&
		, std::array<float, 2> const&
		, std::array<float, 2> const&
		, float const&
		, std::array<float, 3>const&);

class GameObject
{
public:
	~GameObject();
	GameObject() = delete;
	GameObject(int, std::array<float, 2>, std::array<float, 2>, float, std::array<float, 3>);
	GameObject(GameObject const &);
	GameObject &operator=(GameObject const &);

	// Object state
	int						mType;
	std::array<float, 2>	mPos;
	std::array<float, 2>	mScale;
	float					mRotation;
	std::array<float, 3>	mColor;
	// Draw sprite
	virtual void draw(renderFunction const &);
};
#endif //NIBBLER_GAMEOBJECT_HPP
