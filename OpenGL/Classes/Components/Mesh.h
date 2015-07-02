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

	std::vector<GLuint> vaos;
	std::vector<GLuint> indexBuffers;
	std::vector<GLuint> vertexBuffers;
	std::vector<GLuint> uvBuffers;
	std::vector<GLuint> normalBuffers;
	void setUpShape(int shape);
	void setUp();
public:
	Mesh(GameObject *go);
	~Mesh();
	GLuint getVAO(int i);
	int loadOBJ(std::string inputfile);
	int loadCOBJ(std::string inputfile);
	int getShapesCount();
	int getIndexCountForShape(int i);
	void clean();

	// Métodos temporales
	float* getDiffuseForShape(int i);
	float* getAmbientForShape(int i);
};

