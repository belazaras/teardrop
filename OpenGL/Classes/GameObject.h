#pragma once
#include <Transform.h>
#include <Renderer.h>
#include <Mesh.h>

class GameObject
{
private:
	Transform *transform;
	Renderer *renderer;
	Mesh *mesh;
public:
	GameObject();
	~GameObject();

	template <class T>
	T* addComponent();

	template <class T>
	T* getComponent();
};

