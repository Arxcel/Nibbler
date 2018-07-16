
#include "GameObject.hpp"

GameObject::GameObject(int type
		, std::array<float, 2> pos
		, std::array<float, 2> scale
		, float rotation
		, std::array<float, 3> color)
		: mType(type)
		, mPos(pos)
		, mScale(scale)
		, mRotation(rotation)
		, mColor(color)
{
};

GameObject::~GameObject() {};

GameObject::GameObject(GameObject const &) {};

GameObject &GameObject::operator=(GameObject const &) { return *this; };

void GameObject::draw(renderFunction const &functor)
{
	functor(mType, mPos, mScale, mRotation, mColor);
}