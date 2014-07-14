#include "myApp.h"
#include <iostream>
using namespace std;

void myApp::setup()
{
	printf("Starting.\n");

	glClearColor(40 / 255.0, 40 / 255.0, 40 / 255.0, 1); // Medio ilegal aca :P

	Cube = new GameObject();
	Renderer *myRender = Cube->addComponent<Renderer>();
	Mesh *myMesh = Cube->addComponent<Mesh>();
	myMesh->loadOBJ("media/models/cube/cube-uv.obj");

	const int cantX = 5;
	const int cantY = 5;
	GameObject *gOs[cantX][cantY];

	for (int i = 0; i < cantX; i++)
	{
		for (int j = 0; j < cantY; j++)
		{
			gOs[i][j] = new GameObject();
			gOs[i][j]->getComponent<Transform>()->setPosition(j * 2.5, i * 2.5, 0);
			gOs[i][j]->addComponent<Renderer>();
			gOs[i][j]->addComponent<Mesh>()->loadOBJ("media/models/cube/cube-uv.obj");
		}	
	}

	GameObject *SuperCam = new GameObject();
	SuperCam->getComponent<Transform>()->setPosition(5, 5, 25);
	SuperCam->getComponent<Transform>()->setDirection(5, 5, 0);
	Camera *myCam = SuperCam->addComponent<Camera>();
	if (Camera::current())
		printf("Hay Camera");
	
}

void myApp::render()
{
	//printf("Rendering...\n");
}

void myApp::clean()
{
	printf("Cleaning.\n");
	//Cube->getComponent<Mesh>()->clean(); //Se debe hacer automaticamente.
}