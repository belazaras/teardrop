#include "Material.h"


Material::Material()
{
	//BORRAR; SOLO TESTING
	shader = new Shader();
	char *vs = "D:/Desktop/OpenGL Engine/Debug/media/shaders/phong/phong.vs";
	char *fs = "D:/Desktop/OpenGL Engine/Debug/media/shaders/phong/phong.fs";
	shader->load(vs, fs);
}


Material::~Material()
{
}
