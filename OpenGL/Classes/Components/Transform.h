#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Transform :
	public Component
{
private:
	mat4 modelMatrix;
	vec3 *position;
	vec3 *direction; //Ver si no es rotation.
	quat *rotation; // Beta
	vec3 *up;
public:
	Transform();
	~Transform();
	vec3 getPosition();
	void setPosition(vec3 pos);
	void setPosition(float x, float y, float z);
	void setDirection(float x, float y, float z); // Beta
	vec3 getDirection(); // Beta
	vec3 getUp();
	mat4 getModelMatrix();
};

