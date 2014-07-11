#include "Material.h"


Material::Material()
{
	//BORRAR; SOLO TESTING
	shader = new Shader();
	char *vs = "media/shaders/basic/basic.vs";
	char *fs = "media/shaders/basic/basic.fs";
	shader->load(vs, fs);

	texture = new Texture();
	GLuint texID = texture->loadDDS("media/images/dirt.dds");
}


Material::~Material()
{
}
