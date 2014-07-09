#pragma once
#include "Component.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

using namespace glm;
using namespace std;

class Camera :
	public Component
{
private:
	mat4 viewMatrix;
	mat4 projectionMatrix;
	float fieldOfView;
	float aspectRatio;
	float nearClippingPlane, farClippingPlane;
	void setUpProjMatrix();

	// Instances:
	static vector < class Camera * > instances;
public:
	Camera(GameObject *go);
	~Camera();
	static Camera* current();
	bool enabled; // Beta, hacer método, o mover a Behavior.
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
};

