#pragma once
#include <Component.h>
#include <Material.h>


class Renderer :
	public Component
{
private:
	Material *material;	
public:
	bool enabled;
	Renderer(GameObject *go);
	~Renderer();
	void render();
};

