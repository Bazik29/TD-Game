#pragma once

#include "gl_core_4_3.hpp"
#include <GLFW/glfw3.h>

#include <string>

class WindowGLFW
{
	int widht;
	int height;
	GLFWwindow* handle;

public:
	WindowGLFW();
	~WindowGLFW();

	void create(int widht, int height, std::string title, bool resizable = false);
	void destroy();
	bool shouldClose();
	void close();
	void display();
	void resize(int widht, int height);
	GLFWwindow* getHandle() { return handle; };

	void cursorHide();
	void cursorShow();
	void cursorSetState(bool state);
};
