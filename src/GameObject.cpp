
#include "GameObject.hpp"

GameObject::GameObject(int type
		, float posX, float posY, float size
		, float rotation
		, std::array<float, 3> color)
		: mType(type)
		, x(posX), y(posY), mSize(size)
		, mRotation(rotation)
		, mColor(color)
{
};


GameObject::~GameObject() {};

GameObject::GameObject(GameObject const &) {};

GameObject &GameObject::operator=(GameObject const &) { return *this; };

void GameObject::draw(std::shared_ptr<MediaAPI> const &api)
{

	api->drawer(mType, x, y, mSize, mRotation, mColor);
}