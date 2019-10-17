#include "gl_core_4_3.hpp"

#include "WindowGLFW.hpp"
#include "Input.hpp"

#include "Model.hpp"

#include "GLSLProgram.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Render.hpp"

int main(int argc, char const* argv[])
{
	struct Settings
	{
		char* win_title = "TD-game debug";
		unsigned int win_w = 640;
		unsigned int win_h = 480;
		bool win_resizable = false;

		float fov = 45.f;
	} settings;

	std::cout << "-----INIT------\n";
	WindowGLFW window;
	window.create(settings.win_w, settings.win_h, settings.win_title, settings.win_resizable);

	Input input;
	input.init(window);


	GLSLProgram shader;

	shader.attach(fs::path("shaders/simple.vert"));
	shader.attach(fs::path("shaders/simple.frag"));
	shader.link();

	shader.addUniformLocation("model");
	shader.addUniformLocation("view");
	shader.addUniformLocation("projection");


	fs::path path = "models/powergirl/powergirl.obj";
	//fs::path path = "models/Tower.obj";
	std::string name = "tower_1";

	load_model(path, name, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

	Entity test_obj(load_model_OGL(name));

	glm::mat4 view = glm::lookAt(
		glm::vec3(2.5f, 4.7f, 3.8f),
		glm::vec3(0.0f, 2.3f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	glm::mat4 projection = glm::perspective(glm::radians(settings.fov), (float)settings.win_w / (float)settings.win_h, 0.1f, 100.0f);

	Render render;

	render.setShader(shader);


	std::cout << "-----BODY------\n";

	gl::Enable(gl::DEPTH_TEST);
	render.setClearColor();

	while (!window.shouldClose())
	{
		input.update();

		if (input.isKeyDown(Input::Keyboard::ESCAPE))
		{
			window.close();
		}

		render.clear();

		render.setProjection(projection);
		render.setView(view);


		render.draw(test_obj);


		window.display();
	}



	std::cout << "-----END------\n";

	unload_model_OGL(name);
	unload_model(name);

	std::cout << "-----RETURN------\n";
	return 0;
}
