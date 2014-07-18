#pragma once
#include <iostream>
#include <glfw3.h>
#include <unordered_map>
#include <glm\glm.hpp>

using namespace glm;

class Input
{
private:
	static GLFWwindow* window;
	static std::unordered_map<std::string, int> keys;
	static std::unordered_map<std::string, int> mouse_buttons;
	static std::unordered_map<std::string, bool> keyOnce;
	static vec2 windowSize();
public:
	static void setWindow(GLFWwindow* window);
	static bool getKey(std::string key);
	static bool getMouseButton(std::string key);
	static vec2 getMouseDelta(); // Beta
	static void setMousePosition(vec2 mousePos);
	static void centerMouse();
	static void enableMouseCursor(bool enabled);
protected:
	Input();
	~Input();
};

