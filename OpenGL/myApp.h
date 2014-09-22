#pragma once
#include <Engine.h>
#include <GameObject.h>
#include <FPSController.h> // Beta
//#include "UserApp\scripts\myScript.h" // Beta

class myApp : public Engine
{
private:
	GameObject *suzanne;
	GameObject *house;
	GameObject *subaru;
	FPSController *fps; // Beta
	const int cantX = 5;
	const int cantY = 5;
	GameObject *gOs[5][5];
	GameObject *SuperCam;
public:
	void update();
	void clean();
	void setup();
};

DECLARE_MAIN(myApp)