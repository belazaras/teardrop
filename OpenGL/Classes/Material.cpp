#include "Material.h"


Material::Material(char *vs, char *fs)
{
	this->vs = vs;
	this->fs = fs;
	
	shader = new Shader();
	shader->load(vs, fs);

	texture = new Texture();
}


Material::~Material()
{
}

void Material::setShaders(char *vs, char *fs)
{
	shader->clean();
	shader->load(vs, fs);
}

void  Material::reloadShaders()
{
	shader->clean();
	shader->load(this->vs, this->fs);
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