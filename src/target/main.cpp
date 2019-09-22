#include "gl_core_4_3.hpp"

#include "WindowGLFW.hpp"
#include "Input.hpp"

#include <LuaLibrary.h>
#include <LuaBridge.h>

using luabridge::LuaRef;
using luabridge::getGlobal;


int main(int argc, char const* argv[])
{
	lua_State* L = luaL_newstate();
	luaL_dofile(L, "script.lua");
	luaL_openlibs(L);
	lua_pcall(L, 0, 0, 0);

	LuaRef t_window = getGlobal(L, "window");
	std::string titleString = t_window["title"].cast<std::string>();
	int width = t_window["width"].cast<int>();
	int height = t_window["height"].cast<int>();
	bool resizable = t_window["resizable"].cast<bool>();


	WindowGLFW window;
	window.create(width, height, titleString, resizable);

	Input input;
	input.init(window);

	while (!window.shouldClose())
	{
		input.update();

		if (input.isKeyDown(Input::Keyboard::ESCAPE))
		{
			window.close();
		}

		gl::ClearColor(0.5f, 0.7f, 0.0f, 1.0f);
		gl::Clear(gl::COLOR_BUFFER_BIT);

		window.display();
	}

	return 0;
}
