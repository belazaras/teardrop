#pragma once
#include "MainDeferredRenderer.h"

struct SAMPLE_POINTS
{
	glm::vec4     point[256];
	glm::vec4     random_vectors[256];
};

class MainSSAORenderer :
	public MainRenderer
{
private:
	GLuint      gbuffer;
	GLuint      gbuffer_tex[3];
	GLuint      fs_quad_vao;

	Shader *deferred_pass;
	Shader *second_pass;

	//SUPER BETA:
	SAMPLE_POINTS point_data;
	GLuint      points_buffer;
	void generateRandomVectors();
public:
	MainSSAORenderer();
	~MainSSAORenderer();
	void setupGBuffer();
	virtual void render();
};

