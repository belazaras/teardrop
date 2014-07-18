#pragma once
#include <iostream>

class GameObject;

class Component
{
protected:
	GameObject *parent;
public:
	Component();
	~Component();
};


