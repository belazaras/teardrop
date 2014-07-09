#include "Camera.h"

// Included here to avoid circular dependencies.
#include <GameObject.h>

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

	//Setting up View Matrix.
	Transform *t = this->parent->getComponent<Transform>();
	this->viewMatrix = glm::lookAt(
		t->getPosition(),   //Get position from the Transform of the same GO.
		glm::vec3(0, 0, 0), // Beta
		t->getUp()  //Get up dir from the Transform of the same GO.
		);

	// Setting up Projection Matrix with default values.
	this->fieldOfView = 45.0f;
	this->aspectRatio = 16.0f / 9.0f; // Por ahí cambiar a valores de la window.
	this->nearClippingPlane = 0.1f;
	this->farClippingPlane = 100.0f;
	this->setUpProjMatrix();
}

void Camera::setUpProjMatrix()
{
	this->projectionMatrix = glm::perspective(
		this->fieldOfView,       // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		this->aspectRatio,		 // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		this->nearClippingPlane, // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		this->farClippingPlane   // Far clipping plane. Keep as little as possible.
		);
}


Camera::~Camera()
{
}

// Beta: Retrieves the first active camera at the moment. If none returns null.
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
	return viewMatrix; //It's returning a copy, right?
}

mat4 Camera::getProjectionMatrix()
{
	return projectionMatrix;
}