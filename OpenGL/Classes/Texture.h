#pragma once
#include <GL\glew.h>
#include <cstdio>
#include <gli/gli.hpp>

class Texture
{
public:
	Texture();
	~Texture();
	GLuint loadBMP_custom(const char * imagepath); //Super Beta Borrar.
	GLuint loadDDS(const char * imagepath);
};

