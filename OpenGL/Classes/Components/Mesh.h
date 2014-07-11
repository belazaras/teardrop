#pragma once
#include <GL\glew.h>
#include <Component.h>

class GameObject;

class Mesh :
	public Component
{
private:
	GLuint vertexArrayID;
	GLuint vertexBuffer;
	GLuint uvData; // Beta
public:
	Mesh(GameObject *go);
	~Mesh();
	GLuint getVertexBuffer(); // Beta
	GLuint getUVData(); // Beta
};

