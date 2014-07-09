#pragma once
#include <glm\glm.hpp>
#include <Shader.h>

using namespace glm;

class Material
{
private:
	vec3 color;
	//Shader *shader;
public:
	Material();
	~Material();

	//BORRAR
	Shader *shader;
};

