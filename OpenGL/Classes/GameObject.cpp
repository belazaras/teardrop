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

//template <class T>
//template<> T* GameObject::getComponent()
//{
//	T *myS = dynamic_cast<T*> (scripts[0]);
//	return myS;
//}

/*template <class T>
T* GameObject::addComponent()
{
	T *t = new T(this);
	Script *s = dynamic_cast<Script*> (&t);
	if (s)
	{
		scripts.push_back(t);
		return t;
	}
	return nullptr; 
}*/	