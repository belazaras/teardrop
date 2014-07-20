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
	quat *rotation; //beta
	vec3 up;
	void applyRotation(float angle, vec3 orientation); // check
	// beta	
	vec3 look_at;
	vec3 direction;
	
public:
	Transform();
	~Transform();
	vec3 getPosition();
	void setPosition(vec3 pos);
	void setPosition(float x, float y, float z);
	void translate(float x, float y, float z);
	void translate(vec3 translation);
	quat getRotation(); // Beta
	vec3 getUp();
	mat4 getModelMatrix();

	vec3 getDirection(); // Beta

	vec3 getLookAt();
	void setLookAt(vec3 lookAt);
	void rotate(float x, float y, float z);

	// Por ahí hacer privados
	void roll(float angle);
	void yaw(float angle);
	void pitch(float angle);

	// Borrar
	void update();
};

