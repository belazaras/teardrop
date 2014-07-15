#include "FPSController.h"
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
	vec3 v = transform->getPosition();
	float newX = v.x + x;
	transform->setPosition(*new vec3(newX, v.y, v.z));
}

void FPSController::yaw(float y) {
	vec3 v = transform->getPosition();
	float newY = v.y + y;
	transform->setPosition(*new vec3(v.x, newY, v.z));
}

void FPSController::roll(float z) {
	vec3 v = transform->getPosition();
	float newZ = v.z + z;
	transform->setPosition(*new vec3(v.x, v.y, newZ));
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
	
}