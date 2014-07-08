#pragma once
#include <Component.h>
#include <Material.h>


class Renderer :
	public Component
{
private:
	Material *material;
	//GLuint vertexBuffer;
	
public:
	bool enabled;
	Renderer(GameObject *go);
	~Renderer();
	//beta
	void render();
};

