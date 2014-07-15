#pragma once
#include <GL\glew.h>
#include <Component.h>
#include <iostream>
#include <tiny\tiny_obj_loader.h>
#include <time.h>

class GameObject;

class Mesh :
	public Component
{
private:
	std::vector<tinyobj::shape_t> shapes;

	GLuint vao;
	GLuint indexBuffer;
	GLuint vertexBuffer;
	GLuint uvBuffer;
	void setUpVao();
public:
	Mesh(GameObject *go);
	~Mesh();
	//GLuint getVertexBufferID();
	//GLuint getUVBufferID();
	//GLuint getIndexBufferID();
	GLuint getVAO();
	int loadOBJ(std::string inputfile);
	int loadCOBJ(std::string inputfile);
	int getIndexCount();
	void clean();
};

