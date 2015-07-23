#pragma once
#include <vector>
#include <Renderer.h>

using namespace std;

class MainRenderer
{
protected:
	// Singleton instance:
	static MainRenderer *instance;

	// Observer list:
	vector < class Renderer * > renderers;

	//Deferred rendering
	static bool deferred;

	MainRenderer();
	~MainRenderer();

public:
	static MainRenderer *getInstance();
	virtual void render();
	void attach(Renderer *obs);
	static void setDeferredRendering(bool ssao);
};
	
