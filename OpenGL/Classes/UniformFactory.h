#pragma once
#include <Uniform.h>

class UniformFactory
{
public:
	static Uniform* createUniform(const std::string& name, GLenum type);
};

