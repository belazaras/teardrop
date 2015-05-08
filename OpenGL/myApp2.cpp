#include "myApp2.h"

void myApp2::setup()
{
	glClearColor(40 / 255.0, 40 / 255.0, 40 / 255.0, 1);
	Input::enableMouseCursor(false);
	MainRenderer::setDeferredRendering();

	Mesh *sibenikMesh = sibenik.addComponent<Mesh>();
	sibenikMesh->loadCOBJ("media/models/sibenik/output.cobj");

	// MATERIALES
	std::vector<Material> materials;

	Material staklo_plavo = Material("media/shaders/basic/basic.vs", "media/shaders/basic/basic_color.fs");
	materials.push_back(staklo_plavo);

	Material rozeta = Material("media/shaders/phong/phong_textured.vs", "media/shaders/phong/phong_textured.fs");
	rozeta.setTexture("media/models/sibenik/tex/KAMEN-stup.dds");
	materials.push_back(rozeta);

	Material staklo_crveno = Material("media/shaders/basic/basic.vs", "media/shaders/basic/basic_color.fs");
	materials.push_back(staklo_crveno);

	Material zid_vani = Material("media/shaders/phong/phong_textured.vs", "media/shaders/phong/phong_textured.fs");
	rozeta.setTexture("media/models/sibenik/tex/kamen.dds");
	materials.push_back(zid_vani);

	Material sprljci = Material("media/shaders/basic/basic.vs", "media/shaders/basic/basic_color.fs");
	materials.push_back(sprljci);

	Material kamen_zid = Material("media/shaders/phong/phong_textured.vs", "media/shaders/phong/phong_textured.fs");
	kamen_zid.setTexture("media/models/sibenik/tex/kamen.dds");
	materials.push_back(kamen_zid);

	Material zuto = Material("media/shaders/phong/phong.vs", "media/shaders/phong/phong.fs");
	materials.push_back(zuto);

	Material zid_prozor = Material("media/shaders/phong/phong_textured.vs", "media/shaders/phong/phong_textured.fs");
	zid_prozor.setTexture("media/models/sibenik/tex/kamen.dds");
	materials.push_back(zid_prozor);

	Material zid_parapet = Material("media/shaders/basic/basic.vs", "media/shaders/basic/basic.fs");
	zid_parapet.setTexture("media/models/sibenik/tex/KAMEN-stup.dds");
	materials.push_back(zid_parapet);

	Material tepih = Material("media/shaders/sem/sem.vs", "media/shaders/sem/sem.fs");
	tepih.setTexture("media/images/matcaps/skin.dds");
	materials.push_back(tepih);

	Material zeleno = Material("media/shaders/basic/basic.vs", "media/shaders/basic/basic_color.fs");
	materials.push_back(zeleno);

	Material stupovi = Material("media/shaders/phong/phong_textured.vs", "media/shaders/phong/phong_textured.fs");
	stupovi.setTexture("media/models/sibenik/tex/KAMEN-stup.dds");
	materials.push_back(stupovi);

	Material staklo = Material("media/shaders/sem/sem.vs", "media/shaders/sem/sem.fs");
	staklo.setTexture("media/images/matcaps/shiny_red.dds");
	materials.push_back(staklo);

	Material pod = Material("media/shaders/phong/phong_textured.vs", "media/shaders/phong/phong_textured.fs");
	pod.setTexture("media/models/sibenik/tex/mramor6x6.dds");
	materials.push_back(pod);

	Material pod_rub = Material("media/shaders/basic/basic.vs", "media/shaders/basic/basic.fs");
	pod_rub.setTexture("media/models/sibenik/tex/kamen.dds");
	materials.push_back(pod_rub);

	//FIN MATERIALES

	Renderer *sibenikRenderer = sibenik.addComponent<Renderer>();
	sibenikRenderer->setMaterials(materials);
	//sibenikRenderer->setMaterial(sibenikMaterial);
	sibenik.getComponent<Transform>()->translate(0, 0, -5);


	Transform *myTran = camera.getComponent<Transform>();
	myTran->setPosition(-17.37, 2.2, -4.42);
	//myTran->setLookAt(vec3(-15, -13.5, -5.2));
	Camera *myCam = camera.addComponent<Camera>();
	fps = new FPSController(myCam, myTran);

}

void myApp2::update()
{
	double delta = Engine::deltaTime();
	//sibenik.getComponent<Transform>()->rotate(0, 50 * delta, 0);
	fps->update();


	if (Input::getMouseButton("LEFT"))
	{
		Transform *t = camera.getComponent<Transform>();
		printf("Estoy en (%f,%f,%f) mirando a (%f,%f,%f).\n", t->getPosition().x, t->getPosition().y, t->getPosition().z,
			t->getLookAt().x, t->getLookAt().y, t->getLookAt().z);
	}

	if (Input::getKey("R"))
	{
		sibenik.getComponent<Renderer>()->reloadMaterials();
		printf("Shaders recargados");
	}		
}

void myApp2::clean()
{

}