#pragma once
#include "Uniform.h"

template< typename T, int count, UniformType tem_type>
class UniformDerived : public Uniform
{
	//typedef T type;
	const enum attribs{ elementCount = count, elementSize = sizeof(T) };
	T m_elements[elementCount];

public:
	UniformDerived(Shader* sh, const std::string& name, int location) : Uniform(sh, name, location, tem_type){}
	UniformDerived(const std::string& name) : Uniform(name, tem_type){}

	void setValue(T* values)
	{
		memcpy(m_elements, values, attribs::elementCount * attribs::elementSize);
		notifyOwners();
	}

	UniformType getType()
	{
		return type;
	}

	void update(GLuint location)
	{
		updateImpl(location);
	}

protected:
	void updateImpl(GLuint location){ printf("bugaso"); }
};

typedef UniformDerived<float, 1, UniformType::FLOAT> UniformFloat;

typedef UniformDerived<float, 3, UniformType::FLOAT_VEC3> UniformFVec3;
typedef UniformDerived<float, 4, UniformType::FLOAT_VEC4> UniformFVec4;

typedef UniformDerived<float, 9, UniformType::FLOAT_MAT3> UniformFMat3;
typedef UniformDerived<float, 16, UniformType::FLOAT_MAT4> UniformFMat4;


void UniformFVec3::updateImpl(GLuint location)
{
	glUniform3f(location, 1, GL_FALSE, (GLfloat)*m_elements);
}