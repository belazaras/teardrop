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
	bool enabled; // Beta, hacer m�todo, o mover a Behavior.
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
	void update();
};

