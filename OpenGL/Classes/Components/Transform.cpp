#include "Transform.h"
		
Transform::Transform()
{
	modelMatrix = glm::mat4(1.0f);
	position = new vec3(0.0f);
	look_at = vec3(0.0f);
	direction = vec3(0,0,-1);
	up = vec3(0, 1, 0);
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
	return up;
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

void Transform::translate(vec3 translation)
{
	modelMatrix = glm::translate(modelMatrix, translation);
	*position += translation;
	look_at = *position + direction * 1.0f;
}

void Transform::translate(float x, float y, float z)
{
	this->translate(vec3(x, y, z));
}

void Transform::rotate(float x, float y, float z)
{
	//direction = glm::normalize(look_at - *position); // PORQUE BUGUEABA TODO?
	vec3 axis = glm::cross(direction, up);

	quat pitch_quat = glm::angleAxis(x, axis);
	quat yaw_quat = glm::angleAxis(y, up);

	quat rotation = glm::cross(pitch_quat, yaw_quat);
	rotation = glm::normalize(rotation);
	direction = glm::rotate(rotation, direction);

	look_at = *position + direction * 1.0f;

	//////////////////////Debugging:
	vec3 pos = direction;
	printf("%f,%f,%f\n", pos.x, pos.y, pos.z);
	//////////////////////


	/*this->applyRotation(z, vec3(0, 0, 1));
	this->applyRotation(x, vec3(1, 0, 0));
	this->applyRotation(y, vec3(0, 1, 0));*/
}

vec3 Transform::getLookAt()
{
	return look_at;
}

void Transform::setLookAt(vec3 lookAt)
{
	this->look_at = lookAt;
}

vec3 Transform::getDirection() // Beta
{
	return direction;
}
