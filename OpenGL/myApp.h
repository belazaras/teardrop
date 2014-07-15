//#pragma once
#include <Engine.h>
#include <GameObject.h>
#include <FPSController.h> // Beta

class myApp : public Engine
{
private:
	GameObject *Cube;
	FPSController *fps; // Beta
public:
	void render();
	void clean();
	void setup();
};

DECLARE_MAIN(myApp)