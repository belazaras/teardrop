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

Material Renderer::getMaterial(int i = 0)
{
	return this->materials[i];
}

void Renderer::reloadMaterials()
{
	for (int i = 0; i < this->materials.size(); i++)
	{
		materials[i].reloadShaders();
	}
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
			//BORRAR
			this->materials[0].updateShaderUniforms();


			// Bind material's texture.
			glBindTexture(GL_TEXTURE_2D, this->materials[0].getTextureID());

			// Filling the uniform mvp_matrix.
			GLuint MatrixID = glGetUniformLocation(pID, "mvp_matrix");
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

			// Filling the uniform mv_matrix.
			GLuint mv_matrix = glGetUniformLocation(pID, "mv_matrix");
			glUniformMatrix4fv(mv_matrix, 1, GL_FALSE, &modelViewMatrix[0][0]);

			// Filling the uniform model_matrix.
			GLuint model_matrix = glGetUniformLocation(pID, "model_matrix");
			glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &t->getModelMatrix()[0][0]);

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);

			for (int i = 0; i < mesh->getShapesCount(); i++)
			{

				// Super temporal, borrar.
				float* diffuse = mesh->getDiffuseForShape(i);
				float* ambient = mesh->getAmbientForShape(i);

				GLuint diffuse_albedo = glGetUniformLocation(pID, "diffuse_albedo");
				glUniform3fv(diffuse_albedo, 1, &diffuse[0]);

				GLuint ambient_id = glGetUniformLocation(pID, "ambient");
				glUniform3fv(ambient_id, 1, &ambient[0]);


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
				//BORRAR
				this->materials[i].updateShaderUniforms();


				// Bind material's texture.
				glBindTexture(GL_TEXTURE_2D, this->materials[i].getTextureID());

				// Filling the uniform mvp_matrix.
				GLuint MatrixID = glGetUniformLocation(pID, "mvp_matrix");
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

				// Filling the uniform mv_matrix.
				GLuint mv_matrix = glGetUniformLocation(pID, "mv_matrix");
				glUniformMatrix4fv(mv_matrix, 1, GL_FALSE, &modelViewMatrix[0][0]);

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
