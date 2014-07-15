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

	printf("Shape name: %s\n", shapes[0].name.c_str());
	printf("# of vertices : %i\n", shapes[0].mesh.positions.size() / 3);

	this->setUpVao();

	return 0;
}

int Mesh::loadCOBJ(std::string inputfile)
{
	// Thanks to Roald Fernandez from SwarmingLogic for the binary loader/writer.

	// Variables for time measuring.
	clock_t begin, end;
	int ms_spent;

	// Binary file.
	std::ifstream stream(inputfile, std::ios::in | std::ios::binary);

	if (stream) // Doesn't work properly, fix it.
	{
		assert(sizeof(float) == sizeof(uint32));
		const auto sz = sizeof(uint32);

		begin = clock();

		// Reading the binary:
		uint32 nMeshes = 0;
		uint32 nMatProperties = 0;

		// Find out meshes and materials count.
		stream.read((char*)&nMeshes, sz);
		stream.read((char*)&nMatProperties, sz);

		//Resize the vector shapes.
		shapes.resize(nMeshes);
		for (size_t i = 0; i < nMeshes; ++i) {
			uint32 nVertices = 0, nNormals = 0, nTexcoords = 0, nIndices = 0;

			// For each mesh find out the number of vertex, normals, etc.
			stream.read((char*)&nVertices, sz);
			stream.read((char*)&nNormals, sz);
			stream.read((char*)&nTexcoords, sz);
			stream.read((char*)&nIndices, sz);

			// Resize accordingly.
			shapes[i].mesh.positions.resize(nVertices);
			shapes[i].mesh.normals.resize(nNormals);
			shapes[i].mesh.texcoords.resize(nTexcoords);
			shapes[i].mesh.indices.resize(nIndices);

			// Read every chunk of data.
			stream.read((char*)&shapes[i].mesh.positions[0], nVertices  * sz);
			stream.read((char*)&shapes[i].mesh.normals[0], nNormals   * sz);
			stream.read((char*)&shapes[i].mesh.texcoords[0], nTexcoords * sz);
			stream.read((char*)&shapes[i].mesh.indices[0], nIndices   * sz);
			stream.read((char*)&shapes[i].material.ambient[0], 3 * sz);
		}

		// Calculate loading time.
		end = clock();
		ms_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
		printf("Mesh loading: %i ms.\n", ms_spent);

		// Call to set up VAO and VBOs.
		this->setUpVao();
		return 0;
	}
	else
	{
		printf("Error reading file %s. Wrong name?", inputfile);
	}	
}

void Mesh::setUpVao()
{
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
}

int Mesh::getIndexCount()
{
	// Get indices count.
	return shapes[0].mesh.indices.size();
}

void Mesh::clean()
{
	// Delete every VBO and the VAO.
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vao);
}
