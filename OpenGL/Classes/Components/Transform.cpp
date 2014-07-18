#include "Transform.h"
		
Transform::Transform()
{
	modelMatrix = glm::mat4(1.0f);
	position = new vec3(0.0f);
	//direction = new vec3(0.0f); // Borrar
	up = new vec3(0, 1, 0);
	rotation = new quat();
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
	modelMatrix[3] = vec4(pos, 1);
}

void Transform::setPosition(float x, float y, float z)
{
	this->position = new vec3(x,y,z);
	modelMatrix[3] = vec4(x, y, z, 1);
}

quat Transform::getRotation()
{
	return *rotation;
}

vec3 Transform::getUp()
{
	return *up;
}

mat4 Transform::getModelMatrix()
{
	return modelMatrix;
}

void Transform::applyRotation(float angle, vec3 orientation)
{
	quat rot = angleAxis(angle, orientation);
	rotation = &rot;
	modelMatrix *= glm::toMat4(*rotation);
}

void Transform::yaw(float angle)
{
	this->applyRotation(angle, vec3(0, 1, 0));
}

void Transform::pitch(float angle)
{
	this->applyRotation(angle, vec3(1, 0, 0));
}

void Transform::roll(float angle)
{
	this->applyRotation(angle, vec3(0, 0, 1));
}

void Transform::translate(float x, float y, float z)
{
	modelMatrix = glm::translate(modelMatrix, vec3(x, y, z));
	position = &vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
}
