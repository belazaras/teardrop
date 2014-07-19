#pragma once
#include "Component.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <glm/gtc/quaternion.hpp>
#include<glm/gtx/quaternion.hpp>

class Transform;

using namespace glm;
using namespace std;

enum CameraDirection {
	UP, DOWN, LEFT, RIGHT, FORWARD, BACK
};

class Camera :
	public Component
{
private:
	Transform* transform;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	float fieldOfView;
	float aspectRatio;
	float nearClippingPlane, farClippingPlane;
	void setUpProjMatrix();
	void computeViewMatrix();

	// Instances:
	static vector < class Camera * > instances;
public:
	Camera(GameObject *go);
	~Camera();
	static Camera* current();
	bool enabled; // Beta, hacer método, o mover a Behavior.
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
	void update();
	
	// TODO BETA:
	glm::vec3 camera_up;
	glm::vec3 camera_position;			// Usar Transform->pos
	glm::vec3 camera_position_delta;
	glm::vec3 camera_look_at;
	glm::vec3 camera_direction;
	float camera_pitch;
	float camera_heading;
	float camera_scale;
	void Move2D(int x, int y);
	//Change the pitch (up, down) for the free camera
	void ChangePitch(float degrees);
	//Change heading (left, right) for the free camera
	void ChangeHeading(float degrees);
	float max_pitch_rate;
	float max_heading_rate;
	void Move(CameraDirection dir);
};

