#include "MainRenderer.h"
#include <MainDeferredRenderer.h>

MainRenderer *MainRenderer::instance;

bool MainRenderer::deferred;

MainRenderer::MainRenderer()
{
}

MainRenderer::~MainRenderer()
{
}

void MainRenderer::setDeferredRendering()
{
	deferred = true;
	instance = new MainDeferredRenderer();
}

MainRenderer* MainRenderer::getInstance()
{
	if (!instance)
			instance = new MainRenderer();		
	return instance;
}

void MainRenderer::render() {
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