#include "myApp.h"

#include <iostream>


using namespace std;

void myApp::setup()
{
	printf("Starting.\n");

	glClearColor(40 / 255.0, 40 / 255.0, 40 / 255.0, 1); // Medio ilegal aca :P

	Input::enableMouseCursor(false);

	Material *dirt = new Material("media/shaders/basic/basic.vs", "media/shaders/basic/basic.fs");
	dirt->setTexture("media/images/dirt.dds");

	Material *brick = new Material("media/shaders/basic/basic.vs", "media/shaders/basic/basic.fs");
	brick->setTexture("media/images/brick.dds");

	Cube = new GameObject();
	Renderer *myRender = Cube->addComponent<Renderer>();
	myRender->setMaterial(dirt);
	Mesh *myMesh = Cube->addComponent<Mesh>();
	myMesh->loadCOBJ("media/models/rungholt/house.cobj");


	vec3 iniPos = vec3(-5, 25, 30);
	for (int i = 0; i < cantX; i++)
	{
		for (int j = 0; j < cantY; j++)
		{
			gOs[i][j] = new GameObject();
			gOs[i][j]->getComponent<Transform>()->setPosition(iniPos.x + j * 2.8, iniPos.y + i * 2.8, iniPos.z);
			gOs[i][j]->getComponent<Transform>()->yaw(iniPos.y + j * 30);
			gOs[i][j]->getComponent<Transform>()->pitch(iniPos.x + j * 20);
			gOs[i][j]->getComponent<Transform>()->roll(iniPos.z + -j * 20);
			gOs[i][j]->addComponent<Renderer>()->setMaterial(brick);
			gOs[i][j]->addComponent<Mesh>()->loadCOBJ("media/models/cube/cube-uv.cobj");
		}	
	}

	SuperCam = new GameObject();
	Transform *myTran = SuperCam->getComponent<Transform>();
	myTran->setPosition(0, 26, 80);
	myTran->setLookAt(vec3(0, 26, 0));
	Camera *myCam = SuperCam->addComponent<Camera>();

	fps = new FPSController(myCam, myTran);
}

void myApp::render()
{
	//printf("Rendering...\n");
	//printf("Delta time: %f\n", Engine::deltaTime());

	fps->update();
	
	gOs[0][1]->getComponent<Transform>()->yaw(-3);
	gOs[1][2]->getComponent<Transform>()->yaw(1);

	/*if (Input::getKey("Q"))
	{
		gOs[3][2]->getComponent<Transform>()->roll(-10);
	}
	if (Input::getKey("E"))
	{
		gOs[3][2]->getComponent<Transform>()->roll(10);
	}*/		
	if (Input::getMouseButton("LEFT"))
		printf("Apretaron el mouse izq.\n");
}

void myApp::clean()
{
	printf("Cleaning.\n");
	Cube->getComponent<Mesh>()->clean(); //Se debe hacer automaticamente.
}