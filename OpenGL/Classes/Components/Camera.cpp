#include "Camera.h"

// Included here to avoid circular dependencies.
#include <GameObject.h>
#include <Input.h>

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
	transform = this->parent->getComponent<Transform>();
	this->computeViewMatrix();

	// Setting up Projection Matrix with default values.
	this->fieldOfView = 45.0f;
	this->aspectRatio = 16.0f / 9.0f; // Por ahí cambiar a valores de la window.
	this->nearClippingPlane = 0.1f;
	this->farClippingPlane = 100.0f;
	this->setUpProjMatrix();

	// SUPER BETA:
	camera_position = glm::vec3(5, 5, 25);
	camera_look_at = glm::vec3(5, 5, 0);
	camera_up = glm::vec3(0, 1, 0);
	camera_position_delta = glm::vec3(0, 0, 0);
	max_pitch_rate = 5;
	max_heading_rate = 5;
	camera_scale = .05f;
	camera_pitch = 0;
	camera_heading = 0;
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

void Camera::computeViewMatrix()
{
	//this->viewMatrix = glm::lookAt(transform->getPosition(), vec3(0, 0, 0), vec3(0, 1, 0));
	this->viewMatrix = glm::inverse(transform->getModelMatrix());
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

void Camera::update()
{
	//this->computeViewMatrix();

	// Super beta:
	camera_direction = glm::normalize(camera_look_at - camera_position);
	glm::vec3 axis = glm::cross(camera_direction, camera_up);
	glm::quat pitch_quat = glm::angleAxis(camera_pitch, axis);
	glm::quat heading_quat = glm::angleAxis(camera_heading, camera_up);
	glm::quat temp = glm::cross(pitch_quat, heading_quat);
	temp = glm::normalize(temp);
	camera_direction = glm::rotate(temp, camera_direction);
	camera_position += camera_position_delta;
	camera_look_at = camera_position + camera_direction * 1.0f;
	camera_heading *= .6;
	camera_pitch *= .6;
	camera_position_delta = camera_position_delta * .85f;

	viewMatrix = glm::lookAt(camera_position, camera_look_at, camera_up);
}

// Mega beta:

void Camera::Move2D(int x, int y) {
	//compute the mouse delta from the previous mouse position
	//vec2 delta = Input::getMouseDelta();
	//if the camera is moving, meaning that the mouse was clicked and dragged, change the pitch and heading
	ChangePitch(y);
	ChangeHeading(x);
	
	//mouse_position = glm::vec3(x, y, 0);
}

void Camera::ChangePitch(float degrees) {
	//Check bounds with the max pitch rate so that we aren't moving too fast
	if (degrees < -max_pitch_rate) {
		degrees = -max_pitch_rate;
	}
	else if (degrees > max_pitch_rate) {
		degrees = max_pitch_rate;
	}
	camera_pitch += degrees;

	//Check bounds for the camera pitch
	if (camera_pitch > 360.0f) {
		camera_pitch -= 360.0f;
	}
	else if (camera_pitch < -360.0f) {
		camera_pitch += 360.0f;
	}
}

void Camera::ChangeHeading(float degrees) {
	//Check bounds with the max heading rate so that we aren't moving too fast
	if (degrees < -max_heading_rate) {
		degrees = -max_heading_rate;
	}
	else if (degrees > max_heading_rate) {
		degrees = max_heading_rate;
	}
	//This controls how the heading is changed if the camera is pointed straight up or down
	//The heading delta direction changes
	if (camera_pitch > 90 && camera_pitch < 270 || (camera_pitch < -90 && camera_pitch > -270)) {
		camera_heading -= degrees;
	}
	else {
		camera_heading += degrees;
	}
	//Check bounds for the camera heading
	if (camera_heading > 360.0f) {
		camera_heading -= 360.0f;
	}
	else if (camera_heading < -360.0f) {
		camera_heading += 360.0f;
	}
}

void Camera::Move(CameraDirection dir) {
		switch (dir) {
		case UP:
			camera_position_delta += camera_up * camera_scale;
			break;
		case DOWN:
			camera_position_delta -= camera_up * camera_scale;
			break;
		case LEFT:
			camera_position_delta -= glm::cross(camera_direction, camera_up) * camera_scale;
			break;
		case RIGHT:
			camera_position_delta += glm::cross(camera_direction, camera_up) * camera_scale;
			break;
		case FORWARD:
			camera_position_delta += camera_direction * camera_scale;
			break;
		case BACK:
			camera_position_delta -= camera_direction * camera_scale;
			break;
		}
}