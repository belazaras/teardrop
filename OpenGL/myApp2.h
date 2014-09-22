#pragma once
#include <Engine.h>
#include <GameObject.h>

class myApp2 : public Engine
{
private:
	GameObject monkey;
	GameObject camera;
public:
	void update();
	void clean();
	void setup();
};

//DECLARE_MAIN(myApp2)