#pragma once

#define _CRT_SECURE_NO_WARNINGS 1
#include <GL\glew.h>
#include <cstdio>
#include <utility>
#include <unordered_map>
#include <list>

class Uniform;

typedef std::unordered_map<std::string, Uniform*>  UniformsCollection;

typedef std::pair<Uniform*, GLuint> UniLocPair;

class Shader
{
private:
	GLuint load(const char * filename, GLenum shader_type, bool check_errors);
	GLuint program;
	void extractShaderUniforms();
	std::list<UniLocPair> m_dirtyUniforms;
	
public:
	Shader();
	~Shader();
	void load(char *vs_path, char *fs_path);
	void clean();
	GLuint getProgramID();
	void updateUniform(Uniform* uniform, GLuint location);
	void notifyDirty(Uniform* uniform, GLuint location);
	void updateProgram();
	UniformsCollection uniforms;
};

