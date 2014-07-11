#pragma once
#include <glm\glm.hpp>
#include <Shader.h>
#include <Texture.h>

using namespace glm;

class Material
{
private:
	vec3 color;
	Texture *texture;
	//Shader *shader;
public:
	Material();
	~Material();

	//BORRAR
	Shader *shader;
};

