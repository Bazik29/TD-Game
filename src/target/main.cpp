#include "gl_core_4_3.hpp"

#include "WindowGLFW.hpp"
#include "Input.hpp"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main(int argc, char const* argv[])
{
	WindowGLFW window;
	window.create(640, 480, "F", true);

	Input input;
	input.init(window);

	Assimp::Importer importer;

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
