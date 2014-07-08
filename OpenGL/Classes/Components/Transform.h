#pragma once
#include <Component.h>
#include <glm/glm.hpp>

using namespace glm;

class Transform :
	public Component
{
private:
	vec3 *position;
public:
	Transform();
	~Transform();
};

