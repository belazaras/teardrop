#include "Uniform.h"

void Uniform::notifyOwners()
{
	for (int i = 0; i < m_owner.size(); ++i)
	{
		m_owner[i]->notifyDirty(this, m_loc[i]);
	}
}	

Uniform::Uniform(Shader* shader, const std::string& name, unsigned int location, UniformType p_type)
{
	m_name = name;
	type = p_type;
	m_owner.push_back(shader);
	m_loc.push_back(location);
}

Uniform::Uniform(const std::string& name, UniformType p_type)
{
	m_name = name;
	type = p_type;
}

const std::string& Uniform::getName()
{
	return m_name;
}

void Uniform::addOwner(Shader* shader, unsigned int location)
{
	m_owner.push_back(shader);
	m_loc.push_back(location);
}

UniformType Uniform::getType()
{
	return type;
}