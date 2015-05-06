#pragma once
#include "MainRenderer.h"
class MainDeferredRenderer :
	public MainRenderer
{
private:
	GLuint      gbuffer;
	GLuint      gbuffer_tex[3];
	GLuint      fs_quad_vao;

	Shader *deferred_pass;
	Shader *second_pass;
public:
	MainDeferredRenderer();
	~MainDeferredRenderer();
	virtual void render();
	void setupGBuffer();
};

