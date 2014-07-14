#include "Transform.h"

Transform::Transform()
{
	modelMatrix = glm::mat4(1.0f);
	position = new vec3(0.0f);
	direction = new vec3(0.0f);
	up = new vec3(0, 1, 0);
}


Transform::~Transform()
{
}

vec3 Transform::getPosition()
{
	return *position;
}

void Transform::setPosition(vec3 pos)
{
	*this->position = pos;
	modelMatrix = glm::translate(modelMatrix, pos);
}

void Transform::setPosition(float x, float y, float z)
{
	this->position = new vec3(x,y,z);
	modelMatrix = glm::translate(modelMatrix, vec3(x, y, z));
}

void Transform::setDirection(float x, float y, float z)
{
	this->direction = new vec3(x, y, z);
}

vec3 Transform::getDirection()
{
	return *direction;
}

vec3 Transform::getUp()
{
	return *up;
}

mat4 Transform::getModelMatrix()
{
	return modelMatrix;
}
