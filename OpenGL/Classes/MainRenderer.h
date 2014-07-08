#pragma once
#include <vector>
#include <Renderer.h>

using namespace std;

class MainRenderer
{
private:

	// Singleton instance:
	static MainRenderer *instance;

	// Observer list:
	vector < class Renderer * > renderers;

protected:
	MainRenderer();
	~MainRenderer();

public:
	static MainRenderer *getInstance();
	void notify_render();
	void attach(Renderer *obs);
};
	
