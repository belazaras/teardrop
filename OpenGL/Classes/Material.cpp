#include "Material.h"


Material::Material(char *vs, char *fs)
{
	shader = new Shader();
	shader->load(vs, fs);

	texture = new Texture();
}


Material::~Material()
{
}

void Material::setTexture(char *path)
{
	textureID = texture->loadDDS(path);
}

GLuint Material::getTextureID()
{
	return textureID;
}

GLuint Material::getProgramID()
{
	return shader->getProgramID();
}