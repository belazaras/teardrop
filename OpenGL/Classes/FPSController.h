#pragma once

#include <Transform.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
//#include <glfw3.h>
#include <iostream>


// Beta
class FPSController
{
private:
	Transform *transform;
	vec3 pitchYawRoll;
	vec3 velocity;
	float maxVelocitySpeed; // Speed = Velocity Magnitude.
	float velocityDamp; // Fraction of Velocity retained per second.

	float maxRotationSpeed;
	float rotationDamp;
public:
	FPSController();
	~FPSController();

	// Impulse to the x,y,z rotation velocity, in rads/sec.
	void pitch(float x);
	void yaw(float y);
	void roll(float z);

	// Impulse.
	void forward(float s);
	void backward(float s);
	void left(float s);
	void right(float s);

	void update();
};

