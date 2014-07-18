#pragma once
#include <Transform.h>
#include <Renderer.h>
#include <Mesh.h>
#include <Camera.h>
#include <Script.h>

//class Script;

class GameObject
{
private:
	Transform *transform;
	Renderer *renderer;
	Mesh *mesh;
	Camera *camera;
	std::vector<Script*> scripts;
public:
	GameObject();
	~GameObject();

	template <class T>
	T* addComponent();

	template <class T>
	T* getComponent();
};
