#include "GameObject.h"


GameObject::GameObject()
{
	transform = new Transform();
}


GameObject::~GameObject()
{
}

template<> Renderer* GameObject::addComponent()
{
	this->renderer = new Renderer(this);
	return renderer;
}

template<> Mesh* GameObject::addComponent()
{
	this->mesh = new Mesh(this);
	return mesh;
}

template<> Renderer* GameObject::getComponent()
{
	return renderer;
}

template<> Mesh* GameObject::getComponent()
{
	return mesh;
}