#include "WindowGLFW.hpp"
#include "Input.hpp"

int main(int argc, char const* argv[])
{
	WindowGLFW window;
	window.create(640, 480, "F", true);

	Input input;
	input.init(window);

	while (!window.shouldClose())
	{
		input.update();

		if (input.isKeyDown(Input::Keyboard::ESCAPE))
		{
			window.close();
		}

		window.display();
	}

	return 0;
}
