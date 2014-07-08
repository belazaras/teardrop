#include "Mesh.h"
#include <GameObject.h>

Mesh::Mesh(GameObject *go)
{
	this->parent = go;

	//BORRAR O MOVER:	
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	static const GLfloat triangle[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	// Generate 1 buffer, put the resulting identifier in vertexBuffer
	glGenBuffers(1, &vertexBuffer);
	// The following commands will talk about our 'vertexBuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
}


Mesh::~Mesh()
{
}

// Beta
GLuint Mesh::getVertexBuffer()
{
	return vertexBuffer;
}
