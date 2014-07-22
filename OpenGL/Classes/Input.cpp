#include "Input.h"

GLFWwindow *Input::window;

std::unordered_map<std::string, int> Input::keys = { 
	{ "A", GLFW_KEY_A },
	{ "B", GLFW_KEY_B },
	{ "C", GLFW_KEY_C },
	{ "D", GLFW_KEY_D },
	{ "E", GLFW_KEY_E },
	{ "F", GLFW_KEY_F },
	{ "G", GLFW_KEY_G },
	{ "H", GLFW_KEY_H },
	{ "I", GLFW_KEY_I },
	{ "J", GLFW_KEY_J },
	{ "K", GLFW_KEY_K },
	{ "L", GLFW_KEY_L },
	{ "M", GLFW_KEY_M },
	{ "N", GLFW_KEY_N },
	{ "O", GLFW_KEY_O },
	{ "P", GLFW_KEY_P },
	{ "Q", GLFW_KEY_Q },
	{ "R", GLFW_KEY_R },
	{ "S", GLFW_KEY_S },
	{ "T", GLFW_KEY_T },
	{ "U", GLFW_KEY_U },
	{ "V", GLFW_KEY_V },
	{ "W", GLFW_KEY_W },
	{ "X", GLFW_KEY_X },
	{ "Y", GLFW_KEY_Y },
	{ "Z", GLFW_KEY_Z },
	{ "ESCAPE", GLFW_KEY_ESCAPE },
	{ "SPACE", GLFW_KEY_SPACE },
	{ "LSHIFT", GLFW_KEY_LEFT_SHIFT },
	{ "LCTRL", GLFW_KEY_LEFT_CONTROL },
	{ "LALT", GLFW_KEY_LEFT_ALT }
};

std::unordered_map<std::string, int> Input::mouse_buttons = {
	{ "LEFT", GLFW_MOUSE_BUTTON_LEFT },
	{ "RIGHT", GLFW_MOUSE_BUTTON_RIGHT },
	{ "MIDDLE", GLFW_MOUSE_BUTTON_MIDDLE }
};

std::unordered_map<std::string, bool> keyOnce = {
	{ "LEFT", false },
	{ "RIGHT", false },
	{ "MIDDLE", false }
};

Input::Input()
{
}


Input::~Input()
{
}

void Input::setWindow(GLFWwindow* window)
{
	Input::window = window;
}

bool Input::getKey(std::string key)
{
	return glfwGetKey(Input::window, Input::keys[key]);
}

bool Input::getMouseButton(std::string key)
{
	return glfwGetMouseButton(Input::window, Input::mouse_buttons[key]);
}

vec2 Input::getMouseDelta()
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	vec2 mousePos(x, y);
	static vec2 prevMousePos = mousePos;

	vec2 idelta = mousePos - prevMousePos;
	vec2 windowSize = Input::windowSize();

	vec2 delta = vec2(
		(float)idelta.x / (float)windowSize.x,
		(float)idelta.y / (float)windowSize.y
		);

	prevMousePos = mousePos;
	//printf("X: %f, Y: %f\n", delta.x, delta.y);

	return delta;
}

vec2 Input::windowSize()
{
	int width, height;
	glfwGetWindowSize(Input::window, &width, &height);
	return vec2(width, height);
}

void Input::setMousePosition(vec2 mousePos)
{
	glfwSetCursorPos(Input::window, mousePos.x, mousePos.y);
}

void Input::centerMouse()
{
	// Works horribly.
	vec2 pos = Input::windowSize();
	Input::setMousePosition(vec2(pos.x/2,pos.y/2));
}

void Input::enableMouseCursor(bool enabled)
{
	if (enabled)
		glfwSetInputMode(Input::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(Input::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

//bool Input::getMouseButtonUp(std::string key)
//{
//	glfwGetMouseButton(Input::window, Input::mouse_buttons[key]) ? (Input::keyOnce[key] ? false : (Input::keyOnce[key] = true)) : Input::keyOnce[key] = false;
//	//return Input::keyOnce[key];
//	return nullptr;
//}

