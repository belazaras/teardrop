#include "Material.h"


Material::Material()
{
	//BORRAR; SOLO TESTING
	shader = new Shader();
	char *vs = "D:/GL/Teardrop/Debug/media/shaders/basic/basic.vs";
	char *fs = "D:/GL/Teardrop/Debug/media/shaders/basic/basic.fs";
	shader->load(vs, fs);
}


Material::~Material()
{
}
