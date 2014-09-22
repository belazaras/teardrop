#include "MainRenderer.h"

MainRenderer *MainRenderer::instance;

MainRenderer::MainRenderer()
{
}


MainRenderer::~MainRenderer()
{
}

MainRenderer* MainRenderer::getInstance()
{
	if (!instance)
		instance = new MainRenderer();
	return instance;
}

void MainRenderer::notify_render() {
	// Publisher broadcasts
	for (int i = 0; i < renderers.size(); i++)
	{
		if (renderers[i]->enabled)
			renderers[i]->render();
	}	
}

void MainRenderer::attach(Renderer *obs)
{
	renderers.push_back(obs);
}