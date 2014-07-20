#pragma once

#include <Transform.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
//#include <glfw3.h>
#include <iostream>

class Camera;

// Beta
class FPSController
{
private:
	Transform* transform;
	Camera* camera;

	vec3 pitchYawRoll;
	vec3 rotationDamp;

	float velocityDamp;  // Fraction of Velocity retained per second.
	vec3 velocity;

	//float maxVelocitySpeed; // Speed = Velocity Magnitude.
	float movementSpeed; // Acceleration?

	vec3 maxRotationSpeed;

	void readInput();
	vec3 direction();
public:
	FPSController(Camera *cam, Transform *tran);
	~FPSController();

	// Impulse to the x,y,z rotation velocity, in rads/sec.
	void pitch(float degrees);
	void yaw(float degrees);
	void roll(float z);

	// Impulse.
	void up();
	void down();
	void forward();
	void backward();
	void left();
	void right();

	void update();
};

