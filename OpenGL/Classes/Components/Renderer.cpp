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

//Beta
void Renderer::render()
{
	Mesh *mesh = parent->getComponent<Mesh>();

	if (mesh)
	{
		GLuint vBuffer = mesh->getVertexBuffer();

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

		glDisableVertexAttribArray(0);
	}	
}
