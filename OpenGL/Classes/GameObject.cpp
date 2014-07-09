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

template<> Renderer* GameObject::getComponent()
{
	return renderer;
}

template<> Mesh* GameObject::addComponent()
{
	this->mesh = new Mesh(this);
	return mesh;
}

template<> Mesh* GameObject::getComponent()
{
	return mesh;
}

template<> Camera* GameObject::addComponent()
{
	this->camera = new Camera(this);
	return camera;
}

template<> Camera* GameObject::getComponent()
{
	return camera;
}

template<> Transform* GameObject::getComponent()
{
	return transform;
}
