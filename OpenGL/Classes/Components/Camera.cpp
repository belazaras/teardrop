#include "Camera.h"

// Included here to avoid circular dependencies.
#include <GameObject.h>
#include <Input.h>
#include <Transform.h>

vector <Camera*> Camera::instances;

// Camera(float fieldOfView=45.0, float aspectRatio=16/9, float nearClippingPlane=0.1, float farClippingPlane=100)
Camera::Camera(GameObject *go)
{
	// Beta, borrar.
	this->enabled = true;

	// Setting parent GameObject.
	this->parent = go;

	// Adding instance to static collection.
	Camera::instances.push_back(this);

	// Getting Transform from parent.
	transform = this->parent->getComponent<Transform>();


	// Setting up Projection Matrix with default values.
	this->fieldOfView = 45.0f;
	this->aspectRatio = 16.0f / 9.0f; // Por ah� cambiar a valores de la window.
	this->nearClippingPlane = 0.1f;
	this->farClippingPlane = 1000.0f;
	this->setUpProjMatrix();
}

void Camera::setUpProjMatrix()
{
	this->projectionMatrix = glm::perspective(
		this->fieldOfView,       // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90� (extra wide) and 30� (quite zoomed in)
		this->aspectRatio,		 // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		this->nearClippingPlane, // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		this->farClippingPlane   // Far clipping plane. Keep as little as possible.
		);
}

Camera::~Camera()
{
}

// Beta: Retrieves the first active camera at the moment. If none, returns null.
Camera* Camera::current()
{

	int i = 0;
	bool found = false;
	Camera* result = nullptr;

	while (i < instances.size() && !found)
	{
		if (instances[i]->enabled)
		{
			result = instances[i];
			found = true;
		}	
		i++;
	}
	return result;
}

mat4 Camera::getViewMatrix()
{
	//It's returning a copy, right?
	return viewMatrix; 
}

mat4 Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::update()
{
	viewMatrix = glm::lookAt(transform->getPosition(), transform->getLookAt(), transform->getUp());
}