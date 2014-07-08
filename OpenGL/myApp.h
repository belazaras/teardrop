//#pragma once
#include <Engine.h>
#include <GameObject.h>

class myApp : public Engine
{
private:
	GameObject *Cube;
public:
	void render();
	void clean();
	void setup();
};

DECLARE_MAIN(myApp)