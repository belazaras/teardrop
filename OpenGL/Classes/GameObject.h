#pragma once
#include <Transform.h>
#include <Renderer.h>
#include <Mesh.h>
#include <Camera.h>

class GameObject
{
private:
	Transform *transform;
	Renderer *renderer;
	Mesh *mesh;
	Camera *camera;
public:
	GameObject();
	~GameObject();

	template <class T>
	T* addComponent();

	template <class T>
	T* getComponent();
};

