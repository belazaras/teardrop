#pragma once
#include "Component.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <glm/gtc/quaternion.hpp>
#include<glm/gtx/quaternion.hpp>

class Transform;

using namespace glm;
using namespace std;

class Camera :
	public Component
{
private:
	Transform* transform;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	float fieldOfView;
	float aspectRatio;
	float nearClippingPlane, farClippingPlane;
	void setUpProjMatrix();
	void computeViewMatrix();

	// Instances:
	static vector < class Camera * > instances;
public:
	Camera(GameObject *go);
	~Camera();
	static Camera* current();
	bool enabled; // Beta, hacer método, o mover a Behavior.
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
	void update();
	
	// TODO BETA:
	glm::vec3 up;							// Transform
	glm::vec3 position;						// Transform
	glm::vec3 velocity;				// FPS
	glm::vec3 look_at;						// Transform
	glm::vec3 direction;					// Transform

	vec3 pitchYawRoll;						// FPS
	float movementSpeed;					// FPS
	void ChangePitch(float degrees);		// FPS
	void ChangeHeading(float degrees);		// FPS
	float max_pitch_rate;					// FPS
	float max_yaw_rate;						// FPS
	//void Move(CameraDirection dir);			// FPS
};

