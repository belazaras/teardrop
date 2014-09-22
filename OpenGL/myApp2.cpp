#include "myApp2.h"

void myApp2::setup()
{
	Mesh *monkeyMesh = monkey.addComponent<Mesh>();
	monkeyMesh->loadOBJ("media/models/suzanne/suzanne.obj");

	Material *monkeyMaterial = new Material("media/shaders/phong/phong.vs", "media/shaders/phong/phong.fs");

	Renderer *monkeyRenderer = monkey.addComponent<Renderer>();
	monkeyRenderer->setMaterial(monkeyMaterial);

	camera.addComponent<Camera>();

	monkey.getComponent<Transform>()->translate(0, 0, -5);

}

void myApp2::update()
{
	double delta = Engine::deltaTime();
	monkey.getComponent<Transform>()->rotate(0, 50 * delta, 0);
}

void myApp2::clean()
{

}