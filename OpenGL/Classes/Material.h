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
	GLuint textureID;
	Shader *shader;
public:
	Material(char *vs, char *fs);
	~Material();

	void setTexture(char *path);
	GLuint getTextureID();
	GLuint getProgramID();
};

