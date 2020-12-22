#include "WindowGLFW.hpp"
#include <stdexcept>

WindowGLFW::WindowGLFW()
{
	handle = 0;
	widht = 100;
	height = 100;
}

WindowGLFW::~WindowGLFW() {}

void WindowGLFW::create(int widht, int height, std::string title, bool resizable)
{
	if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	handle = glfwCreateWindow(widht, height, title.c_str(), 0, 0);

	if (handle == 0)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to open GLFW window.");
	}

	glfwMakeContextCurrent(handle);

	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
	if (!didLoad)
	{
		glfwTerminate();
		throw std::runtime_error("Number of function that failed to load: " + didLoad.GetNumMissing());
	}

	gl::Viewport(0, 0, widht, height);
}

void WindowGLFW::destroy()
{
	glfwDestroyWindow(handle);
}

bool WindowGLFW::shouldClose()
{
	return glfwWindowShouldClose(handle);
}

void WindowGLFW::close()
{
	glfwSetWindowShouldClose(handle, true);
}

void WindowGLFW::display()
{
	glfwSwapBuffers(handle);
}

void WindowGLFW::resize(int widht, int height)
{
	this->widht = widht;
	this->height = height;
	glfwSetWindowSize(handle, widht, height);
	gl::Viewport(0, 0, widht, height);
}

void WindowGLFW::cursorHide()
{
	glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void WindowGLFW::cursorShow()
{
	glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void WindowGLFW::cursorSetState(bool state)
{
	if (state)
		cursorShow();
	else
		cursorHide();
}

void WindowGLFW::pollEvents()
{
	glfwPollEvents();
}