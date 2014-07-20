#include "myApp.h"

#include <iostream>


using namespace std;

void myApp::setup()
{
	printf("Starting.\n");

	glClearColor(40 / 255.0, 40 / 255.0, 40 / 255.0, 1); // Medio ilegal aca :P

	Input::enableMouseCursor(false);

	

	Cube = new GameObject();
	Renderer *myRender = Cube->addComponent<Renderer>();
	Mesh *myMesh = Cube->addComponent<Mesh>();
	myMesh->loadCOBJ("media/models/rungholt/house.cobj");

	for (int i = 0; i < cantX; i++)
	{
		for (int j = 0; j < cantY; j++)
		{
			gOs[i][j] = new GameObject();
			gOs[i][j]->getComponent<Transform>()->setPosition(j * 2.8, i * 2.8, 0);
			gOs[i][j]->getComponent<Transform>()->yaw(j*30);
			gOs[i][j]->getComponent<Transform>()->pitch(j*20);
			gOs[i][j]->getComponent<Transform>()->roll(-j * 20);
			gOs[i][j]->addComponent<Renderer>();
			gOs[i][j]->addComponent<Mesh>()->loadCOBJ("media/models/cube/cube-uv.cobj");
		}	
	}

	SuperCam = new GameObject();
	Transform *myTran = SuperCam->getComponent<Transform>();
	myTran->setPosition(5, 5, 25);
	myTran->setLookAt(vec3(5, 5, 0));
	Camera *myCam = SuperCam->addComponent<Camera>();

	fps = new FPSController(myCam, myTran);
	/*if (Camera::current())
		printf("Hay Camera\n");*/

	//Cube->addComponent<myScript>();
}

void myApp::render()
{
	//printf("Rendering...\n");
	fps->update();
	//printf("Delta time: %f\n", Engine::deltaTime());
	gOs[0][1]->getComponent<Transform>()->yaw(-3);
	gOs[1][2]->getComponent<Transform>()->yaw(1);

	if (Input::getKey("Q"))
	{
		gOs[3][2]->getComponent<Transform>()->roll(-10);
	}
	if (Input::getKey("E"))
	{
		gOs[3][2]->getComponent<Transform>()->roll(10);
	}
		
	if (Input::getMouseButton("LEFT"))
		printf("Apretaron el mouse izq.\n");

	//vec3 pos = SuperCam->getComponent<Transform>()->getPosition();
	//printf("%f,%f,%f\n", pos.x, pos.y, pos.z);
	/*mat4 mm = SuperCam->getComponent<Transform>()->getModelMatrix();
	printf("%f,%f,%f,%f\n", mm[0][0], mm[0][1], mm[0][2], mm[0][3]);
	printf("%f,%f,%f,%f\n", mm[1][0], mm[1][1], mm[1][2], mm[1][3]);
	printf("%f,%f,%f,%f\n", mm[2][0], mm[2][1], mm[2][2], mm[2][3]);
	printf("%f,%f,%f,%f\n", mm[3][0], mm[3][1], mm[3][2], mm[3][3]);
	printf("-----------------\n");*/
}

void myApp::clean()
{
	printf("Cleaning.\n");
	//Cube->getComponent<Mesh>()->clean(); //Se debe hacer automaticamente.
}