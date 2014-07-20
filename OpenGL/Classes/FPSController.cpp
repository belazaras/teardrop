#include "FPSController.h"

// Included here to avoid circular dependencies.
#include <Engine.h>
#include <Camera.h>

FPSController::FPSController(Camera *cam, Transform *tran)
{
	camera = cam;
	transform = tran;

	pitchYawRoll = vec3(0.0f);
	velocity = vec3(0.0f);

	rotationDamp = vec3(.6, .6, 0);
	velocityDamp = .85f;

	movementSpeed = .05f;
	maxRotationSpeed = vec3(5.0f);	
}


FPSController::~FPSController()
{
}

//void FPSController::roll(float z) {
//	pitchYawRoll.z = pitchYawRoll.z + z;
//}

vec3 FPSController::direction()
{
	return glm::normalize(transform->getLookAt() - transform->getPosition());
}

void FPSController::forward() {
	velocity += direction() * movementSpeed;
}

void FPSController::backward()
{
	velocity -= direction() * movementSpeed;
}

void FPSController::left()
{
	velocity -= glm::cross(direction(), transform->getUp()) * movementSpeed;
}

void FPSController::right()
{
	velocity += glm::cross(direction(), transform->getUp()) * movementSpeed;
}

void FPSController::up()
{
	velocity += transform->getUp() * movementSpeed;
}

void FPSController::down()
{
	velocity -= transform->getUp() * movementSpeed;
}

void FPSController::update()
{
	// Read input.
	this->readInput();

	// Translate the transform.
	transform->translate(velocity);
	// Rotate the transform.
	transform->rotate(pitchYawRoll.x, pitchYawRoll.y, pitchYawRoll.z);

	// Apply rotation damping.
	pitchYawRoll.x *= rotationDamp.x;
	pitchYawRoll.y *= rotationDamp.y;

	// Apply velocity damping.
	velocity = velocity * velocityDamp;	
}

void FPSController::pitch(float degrees) {
	//Check bounds with the max pitch rate so that we aren't moving too fast
	if (degrees < -maxRotationSpeed.x) {
		degrees = -maxRotationSpeed.x;
	}
	else if (degrees > maxRotationSpeed.x) {
		degrees = maxRotationSpeed.x;
	}
	pitchYawRoll.x += degrees;

	//Check bounds for the camera pitch
	if (pitchYawRoll.x > 360.0f) {
		pitchYawRoll.x -= 360.0f;
	}
	else if (pitchYawRoll.x < -360.0f) {
		pitchYawRoll.x += 360.0f;
	}
}

void FPSController::yaw(float degrees) {
	//Check bounds with the max heading rate so that we aren't moving too fast
	if (degrees < -maxRotationSpeed.y) {
		degrees = -maxRotationSpeed.y;
	}
	else if (degrees > maxRotationSpeed.y) {
		degrees = maxRotationSpeed.y;
	}
	//This controls how the heading is changed if the camera is pointed straight up or down
	//The heading delta direction changes
	if (pitchYawRoll.x > 90 && pitchYawRoll.x < 270 || (pitchYawRoll.x < -90 && pitchYawRoll.x > -270)) {
		pitchYawRoll.y -= degrees;
	}
	else {
		pitchYawRoll.y += degrees;
	}
	//Check bounds for the camera heading
	if (pitchYawRoll.y > 360.0f) {
		pitchYawRoll.y -= 360.0f;
	}
	else if (pitchYawRoll.y < -360.0f) {
		pitchYawRoll.y += 360.0f;
	}
}

void FPSController::readInput()
{
	const float rotationAccel = 60.0f; // Rate of acceleration.
	vec2 mPos = Input::getMouseDelta() * rotationAccel;
	this->pitch(-mPos.y);
	this->yaw(-mPos.x);

	movementSpeed = Input::getKey("LSHIFT") ? 0.10f : 0.05f;

	if (Input::getKey("A"))
	{
		this->left();
	}
	if (Input::getKey("D"))
	{
		this->right();
	}
	if (Input::getKey("W"))
	{
		this->forward();
	}
	if (Input::getKey("S"))
	{
		this->backward();
	}
}