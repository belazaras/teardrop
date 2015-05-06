#pragma once
#include <Engine.h>
#include <GameObject.h>
#include <FPSController.h> // Beta

class myApp2 : public Engine
{
private:
	GameObject sibenik;
	GameObject camera;
	FPSController *fps; // Beta
public:
	void update();
	void clean();
	void setup();
};

DECLARE_MAIN(myApp2)