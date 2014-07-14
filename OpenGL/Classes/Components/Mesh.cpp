#include "Mesh.h"
#include <GameObject.h>

Mesh::Mesh(GameObject *go)
{
	this->parent = go;
}


Mesh::~Mesh()
{
}

GLuint Mesh::getVAO()
{
	return vao;
}

int Mesh::loadOBJ(std::string inputfile)
{
	clock_t begin, end;
	int ms_spent;

	// Load the object and measure the time in ms.
	begin = clock();
		std::string err = tinyobj::LoadObj(shapes, inputfile.c_str());
	end = clock();
	ms_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	printf("Mesh loading: %i ms.\n", ms_spent);

	if (!err.empty()) {
		std::cerr << err << std::endl;
		return -1;
	}

	//Generate and bind a VAO that holds the buffers state and bindings.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Generate, bind and load a buffer for the vertices.
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.positions.size() * sizeof(float), &shapes[0].mesh.positions[0], GL_STATIC_DRAW);

	// Enable vertex attribute 0 (It must match the shader location).
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0. It's vertexPosition_modelspace in the shader.
		3,                  // 3 elements for each vertex: x,y,z.
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	//Generate, bind and load a buffer for the UV coordinates.
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.texcoords.size() * sizeof(float), &shapes[0].mesh.texcoords[0], GL_STATIC_DRAW);

	// Enable vertex attribute 1 (It must match the shader location).
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute 1. It's vertexUV in the shader.
		2,                  // 2 elements for each vertex: u,v.
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// Generate, bind and load a buffer for the indices.
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[0].mesh.indices.size() * sizeof(unsigned int), &shapes[0].mesh.indices[0], GL_STATIC_DRAW);

	//Unbind the vao so nobody messes with it.
	glBindVertexArray(0);

	printf("Shape name: %s\n", shapes[0].name.c_str());
	printf("# of vertices : %i\n", shapes[0].mesh.positions.size() / 3);

	return 0;
}

int Mesh::getIndexCount()
{
	return shapes[0].mesh.indices.size();
}

void Mesh::clean()
{
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vao);
}
