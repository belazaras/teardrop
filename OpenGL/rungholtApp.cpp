#include "rungholtApp.h"

#include <iostream>

#include <Uniform.h>
#include <UniformDerived.h>

#include <glm/gtc/type_ptr.hpp>


using namespace std;

void rungholtApp::setup()
{
	printf("Starting.\n");

	glClearColor(68 / 255.0, 169 / 255.0, 255 / 255.0, 1);

	bool ssao = true;
	MainRenderer::setDeferredRendering(ssao);

	Input::enableMouseCursor(false);


	Material dirt = Material("media/shaders/phong/phong_textured.vs", "media/shaders/phong/phong_textured.fs");
	dirt.setTexture("media/images/dirt.dds");

	rungholt_world = new GameObject();
	Renderer *myRender = rungholt_world->addComponent<Renderer>();
	myRender->setMaterial(dirt);
	Mesh *myMesh = rungholt_world->addComponent<Mesh>();
	myMesh->loadCOBJ("media/models/rungholt/rungholt.cobj");

	player_camera = new GameObject();
	Transform *myTran = player_camera->getComponent<Transform>();
	myTran->setPosition(196.59, 143.11, 239.22);
	myTran->setLookAt(vec3(196.072, 142.516, 238.603));
	Camera *myCam = player_camera->addComponent<Camera>();

	fps = new FPSController(myCam, myTran);
}

void rungholtApp::update()
{
	fps->update();

	if (Input::getMouseButton("LEFT"))
	{
		Transform *t = player_camera->getComponent<Transform>();
		printf("Estoy en (%f,%f,%f) mirando a (%f,%f,%f).\n", t->getPosition().x, t->getPosition().y, t->getPosition().z,
			t->getLookAt().x, t->getLookAt().y, t->getLookAt().z);
	}
}

void rungholtApp::clean()
{
	printf("Cleaning.\n");
	rungholt_world->getComponent<Mesh>()->clean();
}
