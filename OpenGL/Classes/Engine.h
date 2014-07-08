//#pragma once
#include <GL\glew.h>
#include <glfw3.h>

#include <MainRenderer.h>

//This class may have to be abstract.
class Engine
{
public:
	int run();
	virtual void render(){};
	virtual void clean(){};
	virtual void setup(){};
	virtual void on_key(int key,int action){}; // It's not being used at the moment.
};

#define DECLARE_MAIN(a)                             \
int main(int argc, const char ** argv)              \
{                                                   \
    a *app = new a;                                 \
    int retCode = app->run();						\
    delete app;                                     \
	return retCode;                                 \
}