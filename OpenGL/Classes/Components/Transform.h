#pragma once
#include <Component.h>
#include <glm/glm.hpp>

using namespace glm;

class Transform :
	public Component
{
private:
	mat4 modelMatrix;
	vec3 *position;
	vec3 *direction; //Ver si no es rotation.
	vec3 *up;
public:
	Transform();
	~Transform();
	vec3 getPosition();
	void setPosition(vec3 pos);
	void setPosition(float x, float y, float z);
	vec3 getUp();
	mat4 getModelMatrix();
};

