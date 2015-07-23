#pragma once

#include <Engine.h>
#include <GameObject.h>
#include <FPSController.h>

class rungholtApp : public Engine
{
private:
	GameObject *rungholt_world;
	FPSController *fps;
	GameObject *player_camera;
public:
	void update();
	void clean();
	void setup();
};

DECLARE_MAIN(rungholtApp)