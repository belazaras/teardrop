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

void Renderer::setMaterial(Material* material)
{
	this->material = material;
}

Material* Renderer::getMaterial()
{
	return material;
}

void Renderer::render()
{
	Transform *t = parent->getComponent<Transform>();
	Camera *c = Camera::current();
	Mesh *mesh = parent->getComponent<Mesh>();

	if (mesh && c) 
	{
		// Bind material's texture.
		glBindTexture(GL_TEXTURE_2D, this->material->getTextureID());

		// Getting the MVP Matrix.
		glm::mat4 MVP = c->getProjectionMatrix() * c->getViewMatrix() * t->getModelMatrix();

		// Getting the shader program ID.
		GLuint pID = this->material->getProgramID();
		glUseProgram(pID);

		// Filling the uniform MVP. What if the shader doesn't have it?
		GLuint MatrixID = glGetUniformLocation(pID, "MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		for (int i = 0; i < mesh->getShapesCount(); i++)
		{
			//Bind mesh's vao.
			glBindVertexArray(mesh->getVAO(i));
			// Draw the triangles!
			glDrawElements(GL_TRIANGLES, mesh->getIndexCountForShape(i), GL_UNSIGNED_INT, (void*)0);
		}
	}	
}
