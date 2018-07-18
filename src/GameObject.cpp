
#include "GameObject.hpp"

GameObject::GameObject(int type
		, float posX, float posY, float size
		, float rotation
		, std::array<float, 3> color)
		: mType(type)
		, mPosX(posX), mPosY(posY), mSize(size)
		, mRotation(rotation)
		, mColor(color)
{
};


GameObject::~GameObject() {};

GameObject::GameObject(GameObject const &) {};

GameObject &GameObject::operator=(GameObject const &) { return *this; };

void GameObject::draw(renderFunction const &functor)
{
	functor(mType, mPosX, mPosY, mSize, mRotation, mColor);
}