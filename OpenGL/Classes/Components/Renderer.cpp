#include "Renderer.h"

// Included here to avoid circular dependencies.
#include <GameObject.h>
#include <MainRenderer.h>

Renderer::Renderer(GameObject *go)
{
	this->parent = go;
	MainRenderer::getInstance()->attach(this);
}

Renderer::~Renderer()
{
}

void Renderer::setMaterial(Material material)
{
	//this->material = material;
	this->materials.push_back(material);
}

void Renderer::setMaterials(std::vector<Material> materials)
{
	this->materials = materials;
}

Material Renderer::getMaterial()
{
	return this->materials[0];
}

void Renderer::reloadMaterials()
{
	for (int i = 0; i < this->materials.size(); i++)
	{
		materials[i].reloadShaders();
	}
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


// Mega RE beta
void Renderer::setUpSSAO()
{
	
	struct
	{
		struct
		{
			GLint           mv_matrix;
			GLint           proj_matrix;
			GLint           shading_level;
		} render;
		struct
		{
			GLint           ssao_level;
			GLint           object_level;
			GLint           ssao_radius;
			GLint           weight_by_angle;
			GLint           randomize_points;
			GLint           point_count;
		} ssao;
	} uniforms;

	//bool  show_shading;
	//bool  show_ao;
	//float ssao_level;
	//float ssao_radius;
	//bool  weight_by_angle;
	//bool randomize_points;
	//unsigned int point_count;

	
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


//MEGA BETA: Modificar para pasar uniforms a Material!
void Renderer::ssao_render(GLuint pID)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, points_buffer);
}

// BETA: It renders multiple textures per object.
void Renderer::render()
{
	Transform *t = parent->getComponent<Transform>();
	Camera *c = Camera::current();
	Mesh *mesh = parent->getComponent<Mesh>();

	if (mesh && c) 
	{
		//Generating the modelViewMatrix.
		glm::mat4 modelViewMatrix = c->getViewMatrix() * t->getModelMatrix();

		// Generating the MVP matrix.
		glm::mat4 MVP = c->getProjectionMatrix() * modelViewMatrix;

		if (materials.size() == 1)
		{
			// Bind material's texture.
			glBindTexture(GL_TEXTURE_2D, this->materials[0].getTextureID());
		
			// Getting the shader program ID.
			GLuint pID = this->materials[0].getProgramID();
			glUseProgram(pID);

			// Filling the uniform MVP. What if the shader doesn't have it?
			GLuint MatrixID = glGetUniformLocation(pID, "MVP");
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

			GLuint mv_matrix = glGetUniformLocation(pID, "mv_matrix");
			glUniformMatrix4fv(mv_matrix, 1, GL_FALSE, &modelViewMatrix[0][0]);

			GLuint proj_matrix = glGetUniformLocation(pID, "proj_matrix");
			glUniformMatrix4fv(proj_matrix, 1, GL_FALSE, &c->getProjectionMatrix()[0][0]);

			for (int i = 0; i < mesh->getShapesCount(); i++)
			{
				//Bind mesh's vao.
				glBindVertexArray(mesh->getVAO(i));

				// Draw the triangles!
				glDrawElements(GL_TRIANGLES, mesh->getIndexCountForShape(i), GL_UNSIGNED_INT, (void*)0);
			}
		}
		else
		{
			for (int i = 0; i < mesh->getShapesCount(); i++)
			{
				glBindTexture(GL_TEXTURE_2D, this->materials[i].getTextureID()); //SUPERBETA

				// Getting the shader program ID.
				GLuint pID = this->materials[i].getProgramID();
				glUseProgram(pID);

				// Filling the uniform MVP. What if the shader doesn't have it?
				GLuint MatrixID = glGetUniformLocation(pID, "MVP");
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

				GLuint mv_matrix = glGetUniformLocation(pID, "mv_matrix");
				glUniformMatrix4fv(mv_matrix, 1, GL_FALSE, &modelViewMatrix[0][0]);

				GLuint proj_matrix = glGetUniformLocation(pID, "proj_matrix");
				glUniformMatrix4fv(proj_matrix, 1, GL_FALSE, &c->getProjectionMatrix()[0][0]);

				//Bind mesh's vao.
				glBindVertexArray(mesh->getVAO(i));

				// Draw the triangles!
				glDrawElements(GL_TRIANGLES, mesh->getIndexCountForShape(i), GL_UNSIGNED_INT, (void*)0);
			}
		}	
	}	
}

void Renderer::deferred_render(GLuint pID)
{
	Transform *t = parent->getComponent<Transform>();
	Camera *c = Camera::current();
	Mesh *mesh = parent->getComponent<Mesh>();

	if (mesh && c)
	{

		//Generating the modelViewMatrix.
		glm::mat4 modelViewMatrix = c->getViewMatrix() * t->getModelMatrix();

		// Generating the MVP matrix.
		glm::mat4 MVP = c->getProjectionMatrix() * modelViewMatrix;

		// Important ;) Make the deferred shader current.
		glUseProgram(pID);

		if (materials.size() == 1)
		{
			// Bind material's texture.
			glBindTexture(GL_TEXTURE_2D, this->materials[0].getTextureID());

			// Filling the uniform mvp_matrix.
			GLuint MatrixID = glGetUniformLocation(pID, "mvp_matrix");
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

			// Filling the uniform model_matrix.
			GLuint model_matrix = glGetUniformLocation(pID, "model_matrix");
			glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &t->getModelMatrix()[0][0]);

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);

			for (int i = 0; i < mesh->getShapesCount(); i++)
			{
				// Bind mesh's vao.
				glBindVertexArray(mesh->getVAO(i));
				// Draw the triangles!
				glDrawElements(GL_TRIANGLES, mesh->getIndexCountForShape(i), GL_UNSIGNED_INT, (void*)0);
			}
		}
		else
		{
			for (int i = 0; i < mesh->getShapesCount(); i++)
			{
				// Bind material's texture.
				glBindTexture(GL_TEXTURE_2D, this->materials[i].getTextureID());

				// Filling the uniform mvp_matrix.
				GLuint MatrixID = glGetUniformLocation(pID, "mvp_matrix");
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

				// Filling the uniform model_matrix.
				GLuint model_matrix = glGetUniformLocation(pID, "model_matrix");
				glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &t->getModelMatrix()[0][0]);

				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);

				// Bind mesh's vao.
				glBindVertexArray(mesh->getVAO(i));
				// Draw the triangles!
				glDrawElements(GL_TRIANGLES, mesh->getIndexCountForShape(i), GL_UNSIGNED_INT, (void*)0);
			}
		}
	}
}
