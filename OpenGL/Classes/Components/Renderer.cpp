#include "Renderer.h"

// Included here to avoid circular dependencies.
#include <GameObject.h>
#include <MainRenderer.h>

Renderer::Renderer(GameObject *go)
{
	this->parent = go;

	MainRenderer::getInstance()->attach(this);

	//TESTING:
	material = new Material();
	//FIN TESTING.
}

Renderer::~Renderer()
{
}

void Renderer::render()
{
	Transform *t = parent->getComponent<Transform>();
	Camera *c = Camera::current();
	Mesh *mesh = parent->getComponent<Mesh>();

	if (mesh && c) 
	{
		//Getting the MVP Matrix.
		glm::mat4 MVP = c->getProjectionMatrix() * c->getViewMatrix() * t->getModelMatrix();

		// Getting the shader program ID.
		GLuint pID = this->material->shader->getProgramID();
		glUseProgram(pID);

		// Filling the uniform MVP. What if the shader doesn't have it?
		GLuint MatrixID = glGetUniformLocation(pID, "MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		//Bind mesh's vao.
		glBindVertexArray(mesh->getVAO());
		// Draw the triangles!
		glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, (void*)0);
	}	
}
