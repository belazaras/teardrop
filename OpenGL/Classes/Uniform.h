#pragma once
#include <vector>
#include <Shader.h>

enum UniformType { ERROR, FLOAT, FLOAT_VEC3, FLOAT_VEC4, FLOAT_MAT3, FLOAT_MAT4 };

class Uniform
{
private:
	std::vector<Shader*> m_owner;  // List containing references to the owners needed so they can be notified.
	std::vector<GLuint> m_loc; // list of locations/handles for the GLSL uniform variable
	std::string m_name; // The name of the uniform variable in the GLSL program

protected:
	void notifyOwners();
	UniformType type;

public:
	Uniform(Shader* sh, const std::string& name, unsigned int location, UniformType p_type);
	Uniform(const std::string& name, UniformType p_type);
	const std::string& getName();
	void addOwner(Shader* shader, unsigned int location);
	UniformType getType();


};


