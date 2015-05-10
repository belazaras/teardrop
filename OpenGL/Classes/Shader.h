#pragma once

#define _CRT_SECURE_NO_WARNINGS 1
#include <GL\glew.h>
#include <cstdio>

class Shader
{
private:
	GLuint load(const char * filename, GLenum shader_type, bool check_errors);
	GLuint program;
	void extractShaderUniforms();
public:
	Shader();
	~Shader();
	void load(char *vs_path, char *fs_path);
	void clean();
	GLuint getProgramID();
};

