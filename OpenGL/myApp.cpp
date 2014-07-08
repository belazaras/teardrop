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
}

void myApp::render()
{
	printf("Rendering...\n");
	Cube->getComponent<Renderer>()->render(); //Hermoso, pero se tendría que llamar automáticamente?
}

void myApp::clean()
{
	printf("Cleaning.\n");
}