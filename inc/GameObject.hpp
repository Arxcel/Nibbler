/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arxcel <arxcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 21:07:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/09/30 17:15:35 by arxcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_GAMEOBJECT_HPP
#define NIBBLER_GAMEOBJECT_HPP
#include <array>
#include "MediaAPIFunctions.hpp"
#include "MediaAPI.hpp"

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
	virtual void draw(std::shared_ptr<MediaAPI> const &);
};
#endif //NIBBLER_GAMEOBJECT_HPP
