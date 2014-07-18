#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include<glm/gtx/quaternion.hpp>

using namespace glm;

class Transform :
	public Component
{
private:
	mat4 modelMatrix;
	vec3 *position;
	quat *rotation;
	vec3 *up;
	void applyRotation(float angle, vec3 orientation);
public:
	Transform();
	~Transform();
	vec3 getPosition();
	void setPosition(vec3 pos);
	void setPosition(float x, float y, float z);
	void translate(float x, float y, float z);
	quat getRotation(); // Beta
	vec3 getUp();
	mat4 getModelMatrix();
	void yaw(float angle);
	void pitch(float angle);
	void roll(float angle);
};

