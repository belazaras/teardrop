#pragma once
#include <glm\glm.hpp>
#include <Shader.h>
#include <Texture.h>

using namespace glm;

class Material
{
private:
	char *vs, *fs;
	vec3 color;
	Texture *texture;
	GLuint textureID;
	Shader *shader;
public:
	Material(char *vs, char *fs);

	void setTexture(char *path);
	void setShaders(char *vs, char *fs);
	void reloadShaders();
	GLuint getTextureID();
	GLuint getProgramID();
	
	void updateShaderUniforms();
	UniformsCollection* getShaderUniforms();
	Uniform* getShaderUniform(std::string name);
};

