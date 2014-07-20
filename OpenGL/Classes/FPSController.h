#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

#include <Transform.h>
class Camera;

// It has to use deltaTime!
class FPSController
{
private:
	Transform* transform;
	Camera* camera;

	vec3 pitchYawRoll; // Rotation on the three axis.
	vec3 rotationDamp; // Fraction of Rotation retained per second.

	vec3 velocity;		// Velocity on the three axis.
	float velocityDamp;  // Fraction of Velocity retained per second.
	
	//float maxVelocitySpeed; // Speed = Velocity Magnitude.
	float movementSpeed; // Acceleration?
	vec3 maxRotationSpeed;

	// Read input from Mouse and Keyboard.
	void readInput();

	//Calculate direction based on position and lookAt.
	vec3 direction();

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
public:
	FPSController(Camera *cam, Transform *tran);
	~FPSController();
	void update();
};

