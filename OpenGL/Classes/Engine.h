#pragma once
#include <GL\glew.h>
#include <glfw3.h>

#include <MainRenderer.h>
#include <Input.h>
#include <Camera.h>

//This class may have to be abstract.
class Engine
{
private:
	GLFWwindow* window;
public:
	int run();
	virtual void update(){};
	virtual void clean(){};
	virtual void setup(){};
	virtual void on_key(int key,int action){}; // It's not being used at the moment.
	static float deltaTime();
};

#define DECLARE_MAIN(a)                             \
int main(int argc, const char ** argv)              \
{                                                   \
    a *app = new a;                                 \
    int retCode = app->run();						\
    delete app;                                     \
	return retCode;                                 \
}