#include "Shader.h"

#include <UniformFactory.h>
#include <UniformDerived.h>

Shader::Shader()
{
}


Shader::~Shader()
{
}

GLuint Shader::getProgramID()
{
	return program;
}

void Shader::clean()
{
	glDeleteProgram(program);
}

void Shader::extractShaderUniforms()
{
	GLuint pId = getProgramID();
	const int BUFF_SIZE = 255;
	int count;
	glGetProgramiv(pId, GL_OBJECT_ACTIVE_UNIFORMS_ARB, &count);

	for (int i = 0; i < count; ++i)
	{
		char name[BUFF_SIZE]; // for holding the variable name
		GLint size = BUFF_SIZE;
		GLenum type;
		GLsizei length;
		GLsizei bufSize = BUFF_SIZE;
		glGetActiveUniform(pId, i, bufSize, &length, &size, &type, name);
		int location = glGetUniformLocation(pId, name);

		Uniform* uniform = UniformFactory::createUniform(name, type);
		uniform->addOwner(this,location);
		uniforms.insert(std::make_pair(uniform->getName(), uniform));

		//Borrar
		const char* uni_types[6] = { "Error", "FLOAT", "FLOAT_VEC3", "FLOAT_VEC4", "FLOAT_MAT3", "FLOAT_MAT4" };
		printf("Uniform name: %s. Type: %s.\n", uniform->getName().c_str(), uni_types[uniform->getType()]);	
	}
	printf("---------------\n");
}

void Shader::updateUniform(Uniform* uniform, GLuint location)
{
	switch (uniform->getType())
	{
		case UniformType::FLOAT:
		{
			UniformFloat* unformFloat = static_cast<UniformFloat*>(uniform);
			unformFloat->update(location);
				break;
		}

		case UniformType::FLOAT_VEC3:
		{
			UniformFVec3* unformVec = static_cast<UniformFVec3*>(uniform);
			unformVec->update(location);
			break;
		}

		case UniformType::FLOAT_VEC4:
		{
			UniformFVec4* unformVec4 = static_cast<UniformFVec4*>(uniform);
			unformVec4->update(location);
			break;
		}
		
		case UniformType::FLOAT_MAT3:
		{
			UniformFMat3* unformMat = static_cast<UniformFMat3*>(uniform);
			unformMat->update(location);
			break;
		}

		case UniformType::FLOAT_MAT4:
		{
			UniformFMat4* unformMat = static_cast<UniformFMat4*>(uniform);
			unformMat->update(location);
			break;
		}	
	}
}

void Shader::updateProgram()
{
	while (!m_dirtyUniforms.empty())
	{
		UniLocPair& top = m_dirtyUniforms.front();

		Uniform* currUniform = top.first;
		GLuint currLoc = top.second;

		updateUniform(currUniform, currLoc);
		m_dirtyUniforms.pop_front();
	}
}

void Shader::notifyDirty(Uniform* uniform, GLuint location)
{
	UniLocPair asd = UniLocPair(uniform, location);

	m_dirtyUniforms.push_back(asd);
}

void Shader::load(char *vs_path, char *fs_path)
{
	GLuint vs;
	GLuint fs;

	vs = load(vs_path, GL_VERTEX_SHADER, true);
	fs = load(fs_path, GL_FRAGMENT_SHADER, true);

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	
	glDeleteProgram(vs);
	glDeleteProgram(fs);

	//BETA:
	extractShaderUniforms();
}

GLuint Shader::load(const char * filename, GLenum shader_type, bool check_errors)
{
	GLuint result = 0;
	FILE * fp;
	size_t filesize;
	char * data;	

	fp = fopen(filename, "rb");

	if (!fp) {
		printf("Can't read the file: %s.", filename);
		return 0;
	}
		
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	data = new char[filesize + 1];

	if (!data)
		goto fail_data_alloc;

	fread(data, 1, filesize, fp);
	data[filesize] = 0;
	fclose(fp);

	result = glCreateShader(shader_type);

	if (!result)
		goto fail_shader_alloc;

	glShaderSource(result, 1, (const GLchar**)&data, NULL);

	delete[] data;

	glCompileShader(result);

	if (check_errors)
	{
		GLint status = 0;
		glGetShaderiv(result, GL_COMPILE_STATUS, &status);

		if (!status)
		{
			char buffer[4096];
			glGetShaderInfoLog(result, 4096, NULL, buffer);
#ifdef _WIN32
			printf(filename);
			printf(":");
			printf(buffer);
			printf("\n");
#else
			fprintf(stderr, "%s: %s\n", filename, buffer);
#endif
			goto fail_compile_shader;
		}
	}

	return result;

fail_compile_shader:
	glDeleteShader(result);

fail_shader_alloc:;
fail_data_alloc:
	return result;
}
