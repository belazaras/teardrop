#include "myApp.h"

#include <iostream>

#include <Uniform.h>
#include <UniformDerived.h>

#include <glm/gtc/type_ptr.hpp>


using namespace std;

void myApp::setup()
{
	printf("Starting.\n");

	//glClearColor(68 / 255.0, 169 / 255.0, 255 / 255.0, 1); // Medio ilegal aca :P

	bool ssao = true;
	//MainRenderer::setDeferredRendering(ssao);

	Input::enableMouseCursor(false);

	/*Material comun = Material("media/shaders/basic/basic.vs", "media/shaders/basic/basic_color.fs");*/

	Material dirt = Material("media/shaders/phong/phong_textured.vs", "media/shaders/phong/phong_textured.fs");
	dirt.setTexture("media/images/dirt.dds");

	//Material brick = Material("media/shaders/basic/basic.vs", "media/shaders/basic/basic.fs");
	//brick.setTexture("media/images/brick.dds");

	Material suza = Material("media/shaders/sem/sem.vs", "media/shaders/sem/sem.fs");
	suza.setTexture("media/images/matcaps/skin.dds");

	//Material suba = Material("media/shaders/phong/phong.vs", "media/shaders/phong/phong.fs");

	Material suba2 = Material("media/shaders/sem/sem.vs", "media/shaders/sem/sem.fs");
	suba2.setTexture("media/images/matcaps/shiny_red.dds");

	//house = new GameObject();
	//Renderer *myRender = house->addComponent<Renderer>();
	//myRender->setMaterial(dirt);
	//Mesh *myMesh = house->addComponent<Mesh>();
	//myMesh->loadCOBJ("media/models/rungholt/rungholt.cobj");

	suzanne = new GameObject();
	suzanne->getComponent<Transform>()->setPosition(20, 30, 30);
	suzanne->getComponent<Transform>()->scale(6);
	Renderer *suzaRender = suzanne->addComponent<Renderer>();
	suzaRender->setMaterial(suba2);
	Mesh *suzaMesh = suzanne->addComponent<Mesh>();
	suzaMesh->loadCOBJ("media/models/suzanne/suzanne.cobj");

	/*subaru = new GameObject();
	subaru->getComponent<Transform>()->setPosition(10, 0, 50);
	subaru->getComponent<Transform>()->scale(6);
	Renderer *subaRender = subaru->addComponent<Renderer>();
	subaRender->setMaterial(suba2);
	Mesh *subaMesh = subaru->addComponent<Mesh>();
	subaMesh->loadCOBJ("media/models/subaru/subaru.cobj");

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
	}*/

	SuperCam = new GameObject();
	Transform *myTran = SuperCam->getComponent<Transform>();
	myTran->setPosition(196.59, 143.11, 239.22);
	myTran->setLookAt(vec3(196.072, 142.516, 238.603));
	Camera *myCam = SuperCam->addComponent<Camera>();

	fps = new FPSController(myCam, myTran);
}

void myApp::update()
{
	//printf("Rendering...\n");
	//printf("Delta time: %f\n", Engine::deltaTime());

	//if (Input::getKey("E"))
	//{
	//	//MEGATESTING
	//	UniformsCollection* cole = house->getComponent<Renderer>()->getMaterial(0).getShaderUniforms();
	//	Uniform* uni = cole->at("MVP");
	//	
	//	UniformFVec3* unformVec = static_cast<UniformFVec3*>(uni);
	//	
	//	vec3 asd = vec3(0.55, 0.33, 0.10);
	//	unformVec->setValue(glm::value_ptr(asd));

	//	printf("Name: %s.\n", uni->getName().c_str());

	//}

	fps->update();
	
	//gOs[0][1]->getComponent<Transform>()->yaw(-3);
	//gOs[1][2]->getComponent<Transform>()->yaw(1);

	//suzanne->getComponent<Transform>()->yaw(50 * Engine::deltaTime());
	/*if (Input::getKey("Q"))
	{
		gOs[3][2]->getComponent<Transform>()->roll(-10);
	}
	if (Input::getKey("E"))
	{
		gOs[3][2]->getComponent<Transform>()->roll(10);
	}*/		
	if (Input::getMouseButton("LEFT"))
	{
		Transform *t = SuperCam->getComponent<Transform>();
		printf("Estoy en (%f,%f,%f) mirando a (%f,%f,%f).\n", t->getPosition().x, t->getPosition().y, t->getPosition().z,
			t->getLookAt().x, t->getLookAt().y, t->getLookAt().z);
	}
}

void myApp::clean()
{
	printf("Cleaning.\n");
	//house->getComponent<Mesh>()->clean(); //Se debe hacer automaticamente.
}