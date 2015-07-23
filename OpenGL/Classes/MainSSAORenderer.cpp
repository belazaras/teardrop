#include "MainSSAORenderer.h"

//Modificar para pasar uniforms a Material!

enum
{
	MAX_DISPLAY_WIDTH = 1280,
	MAX_DISPLAY_HEIGHT = 720
};

MainSSAORenderer::MainSSAORenderer()
{
	this->setupGBuffer();

	glGenVertexArrays(1, &fs_quad_vao);
	glBindVertexArray(fs_quad_vao);

	deferred_pass = new Shader();
	deferred_pass->load("media/shaders/ssao/1st_pass.vs", "media/shaders/ssao/1st_pass.fs");

	second_pass = new Shader();
	second_pass->load("media/shaders/ssao/ssao.vs", "media/shaders/ssao/ssao.fs");

	this->generateRandomVectors();
}

// Random number generator
static unsigned int seed = 0x13371337;

static inline float random_float()
{
	float res;
	unsigned int tmp;

	seed *= 16807;

	tmp = seed ^ (seed >> 4) ^ (seed << 15);

	*((unsigned int *)&res) = (tmp >> 9) | 0x3F800000;

	return (res - 1.0f);
}

void MainSSAORenderer::generateRandomVectors()
{
	for (int i = 0; i < 256; i++)
	{
		do
		{
			point_data.point[i][0] = random_float() * 2.0f - 1.0f;
			point_data.point[i][1] = random_float() * 2.0f - 1.0f;
			point_data.point[i][2] = random_float(); //  * 2.0f - 1.0f;
			point_data.point[i][3] = 0.0f;
		} while (length(point_data.point[i]) > 1.0f);
		normalize(point_data.point[i]);
	}
	for (int i = 0; i < 256; i++)
	{
		point_data.random_vectors[i][0] = random_float();
		point_data.random_vectors[i][1] = random_float();
		point_data.random_vectors[i][2] = random_float();
		point_data.random_vectors[i][3] = random_float();
	}

	glGenBuffers(1, &points_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, points_buffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SAMPLE_POINTS), &point_data, GL_STATIC_DRAW);
}

void MainSSAORenderer::setupGBuffer()
{
	printf("Setting up G-Buffer!.\n");

	glGenFramebuffers(1, &gbuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gbuffer);

	glGenTextures(3, gbuffer_tex);
	glBindTexture(GL_TEXTURE_2D, gbuffer_tex[0]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32UI, MAX_DISPLAY_WIDTH, MAX_DISPLAY_HEIGHT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, gbuffer_tex[1]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, MAX_DISPLAY_WIDTH, MAX_DISPLAY_HEIGHT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, gbuffer_tex[2]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, MAX_DISPLAY_WIDTH, MAX_DISPLAY_HEIGHT);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gbuffer_tex[0], 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, gbuffer_tex[1], 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, gbuffer_tex[2], 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void MainSSAORenderer::render()
{
	//printf("Deferred rendering.\n");

	static const GLuint uint_zeros[] = { 0, 0, 0, 0 };
	static const GLfloat float_zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const GLfloat float_ones[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

	glBindFramebuffer(GL_FRAMEBUFFER, gbuffer);
	glViewport(0, 0, MAX_DISPLAY_WIDTH, MAX_DISPLAY_HEIGHT);
	glDrawBuffers(2, draw_buffers);
	glClearBufferuiv(GL_COLOR, 0, uint_zeros);
	glClearBufferuiv(GL_COLOR, 1, uint_zeros);
	glClearBufferfv(GL_DEPTH, 0, float_ones);

	
	//Bind random vectors buffer
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, points_buffer);

	GLuint pID = deferred_pass->getProgramID();

	//NOTIFY
	for (int i = 0; i < renderers.size(); i++)
	{
		if (renderers[i]->enabled)
			renderers[i]->deferred_render(pID);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, MAX_DISPLAY_WIDTH, MAX_DISPLAY_HEIGHT);
	glDrawBuffer(GL_BACK);


	//2nd pass:
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuffer_tex[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuffer_tex[1]);

	GLuint second = second_pass->getProgramID();
	glUseProgram(second);

	glDisable(GL_DEPTH_TEST);

	glBindVertexArray(fs_quad_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


