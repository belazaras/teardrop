#pragma once

class GameObject;

class Component
{
protected:
	GameObject *parent;
public:
	Component();
	~Component();
};

