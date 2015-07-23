#include "MainRenderer.h"
#include <MainDeferredRenderer.h>
#include <MainSSAORenderer.h>

MainRenderer *MainRenderer::instance;

bool MainRenderer::deferred;

MainRenderer::MainRenderer()
{
}

MainRenderer::~MainRenderer()
{
}

void MainRenderer::setDeferredRendering(bool ssao)
{
	deferred = true;
	// Mejorar
	if (ssao)
		instance = new MainSSAORenderer();
	else
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