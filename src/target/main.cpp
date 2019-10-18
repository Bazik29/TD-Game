#include "gl_core_4_3.hpp"

#include "WindowGLFW.hpp"
#include "Input.hpp"

#include "Model.hpp"

#include "GLSLProgram.hpp"


#include <random>

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
		bool win_resizable = true;

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


	fs::path path = "models/cube.obj";
	//fs::path path = "models/Tower.obj";
	std::string name = "tower_1";

	load_model(path, name, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

	std::vector<Entity> entites;
	int n = 5;
	float shift = 2.5f;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			float shift_x = shift * (j - n / 2);
			float shift_y = shift * (i - n / 2);

			Entity& ent = entites.emplace_back(load_model_OGL(name));
			ent.modelMat4 = glm::translate(ent.modelMat4, glm::vec3(shift_x, shift_y, 0.0f));
		}

	std::vector<glm::vec3> direction(entites.size());
	std::mt19937 gen(5005);
	std::uniform_int_distribution<> uid(-20, 20);
	std::generate(direction.begin(), direction.end(),
		[&uid, &gen]() -> glm::vec3
	{
		return glm::vec3(uid(gen), uid(gen), uid(gen));
	}
	);


	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 20.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	glm::mat4 projection = glm::perspective(glm::radians(settings.fov), (float)settings.win_w / (float)settings.win_h, 0.1f, 100.0f);

	Render render;

	render.setShader(shader);


	std::cout << "-----BODY------\n";


	gl::Enable(gl::DEPTH_TEST);
	render.setClearColor();

	double lastTime = glfwGetTime();
	float deltaTime;

	while (!window.shouldClose())
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;


		input.update();

		if (input.isKeyDown(Input::Keyboard::ESCAPE))
		{
			window.close();
		}
		if (input.isKeyDown(Input::Keyboard::NUM_1))
		{
			int w = 640, h = 480;
			window.resize(w, h);
			projection = glm::perspective(glm::radians(settings.fov), (float)w / (float)h, 0.1f, 100.0f);
		}
		if (input.isKeyDown(Input::Keyboard::NUM_2))
		{
			int w = 1280, h = 720;
			window.resize(w, h);
			projection = glm::perspective(glm::radians(settings.fov), (float)w / (float)h, 0.1f, 100.0f);
		}



		for (int i = 0; i < entites.size(); i++)
		{
			entites[i].modelMat4 = glm::rotate(entites[i].modelMat4, deltaTime, direction[i]);
		}


		render.clear();

		render.setProjection(projection);
		render.setView(view);

		for (auto& enti : entites)
		{
			render.draw(enti);
		}

		window.display();
	}


	std::cout << "-----END------\n";

	unload_model_OGL(name);
	unload_model(name);


	window.destroy();

	std::cout << "-----RETURN------\n";
	return 0;
}
