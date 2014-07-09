#include "myApp.h"
#include <iostream>
using namespace std;

void myApp::setup()
{
	printf("Starting.\n");

	glClearColor(40 / 255.0, 40 / 255.0, 40 / 255.0, 1);

	Cube = new GameObject();
	Renderer *myRender = Cube->addComponent<Renderer>();
	Mesh *myMesh = Cube->addComponent<Mesh>();

	GameObject *SuperCam = new GameObject();
	SuperCam->getComponent<Transform>()->setPosition(4, 3, 3);
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
}