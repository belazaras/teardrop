#include "UniformFactory.h"

#include <UniformDerived.h>

Uniform* UniformFactory::createUniform(const std::string& name, GLenum type)
{
	Uniform* uniform;

	switch (type)
	{
		case GL_FLOAT:
		{
			uniform = new UniformFloat(name);
			break;
		}

		case GL_FLOAT_VEC3:
		{
			uniform = new UniformFVec3(name);
			break;
		}

		case GL_FLOAT_VEC4:
		{
			uniform = new UniformFVec4(name);
			break;
		}

		case GL_FLOAT_MAT3:
		{
			uniform = new UniformFMat3(name);
			break;
		}

		case GL_FLOAT_MAT4:
		{
			uniform = new UniformFMat4(name);
			break;
		}

		default:
		{
			std::string error = name + " (Error)";
			uniform = new UniformFMat4(error);
			break;
		}

	}
	return uniform;
}