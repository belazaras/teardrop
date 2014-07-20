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
	vec3 position;
	vec3 up;
	vec3 look_at;
	vec3 direction;

	// Delete in the future:
	quat rotation; 
	void applyRotation(float angle, vec3 orientation);
public:
	Transform();
	~Transform();

	vec3 getPosition();
	void setPosition(vec3 pos); // Does this work well?
	void setPosition(float x, float y, float z);

	void translate(vec3 translation);
	void translate(float x, float y, float z);

	void rotate(float x, float y, float z);
	
	vec3 getUp();
	mat4 getModelMatrix();

	vec3 getLookAt();
	void setLookAt(vec3 lookAt);
	
	// Por ahí borrarlos y solo permitir el rotate():
	void roll(float angle);
	void yaw(float angle);
	void pitch(float angle);
};

