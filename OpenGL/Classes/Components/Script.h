#pragma once

#include <Component.h>

class Script :
	public Component
{
public:
	Script(GameObject *go);
	~Script();
	virtual void start(){};
	virtual void update(){};
};

