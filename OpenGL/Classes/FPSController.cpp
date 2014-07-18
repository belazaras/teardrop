#include "FPSController.h"

#include <Engine.h>

FPSController::FPSController()
{
	velocity = vec3(0.0f);
	maxVelocitySpeed = 100.0f;
	velocityDamp = 0.001f;
	maxRotationSpeed = 10.0f;
	rotationDamp = 0.000005f;
}


FPSController::~FPSController()
{
}

void FPSController::pitch(float x) {
	pitchYawRoll.x = pitchYawRoll.x + x;
}

void FPSController::yaw(float y) {
	pitchYawRoll.y = pitchYawRoll.y + y;
}

void FPSController::roll(float z) {
	pitchYawRoll.z = pitchYawRoll.z + z;
}

void FPSController::forward(float s) {
	velocity += transform->getPosition() * s;
}

void FPSController::backward(float s) {
	forward(-s);
}

void FPSController::update() {

	//Get mouse position
	double xpos, ypos;
	printf("Delta: %f\n", Engine::deltaTime());
	
}