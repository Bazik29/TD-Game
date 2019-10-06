#include "gl_core_4_3.hpp"

#include "WindowGLFW.hpp"
#include "Input.hpp"

#include "ModelGL.hpp"

#include "GLSLProgram.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main(int argc, char const* argv[])
{
	std::cout << "-----INIT------\n";
	WindowGLFW window;
	window.create(500, 500, "!", 0);

	Input input;
	input.init(window);


	GLSLProgram shader;

	shader.attach(fs::path("shaders/simple.vert"));
	shader.attach(fs::path("shaders/simple.frag"));
	shader.link();


	fs::path path = "models/powergirl/powergirl.obj";
	std::string name = "tower_1";

	load_model(path, name);
	ModelGL* modelGL = load_model_OGL(name);


	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 view;
	view = glm::lookAt(
		glm::vec3(0.0f, 3.0f, -5.5f),
		glm::vec3(0.0f, 2.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)500 / (float)500, 0.1f, 100.0f);

	
	shader.addUniformLocation("model");
	shader.addUniformLocation("view");
	shader.addUniformLocation("projection");


	std::cout << "-----BODY------\n";
	while (!window.shouldClose())
	{
		input.update();

		if (input.isKeyDown(Input::Keyboard::ESCAPE))
		{
			window.close();
		}

		gl::Enable(gl::DEPTH_TEST);

		gl::ClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);


		shader.start();

		shader.setUniform("model", model);
		shader.setUniform("view", view);
		shader.setUniform("projection", projection);

		for (const auto& meshGL : modelGL->meshesGL)
		{
			GLuint id_diff = meshGL.materialGL.textures_id.at(TextureType::DIFFUSE);
			gl::ActiveTexture(gl::TEXTURE0);
			gl::BindTexture(gl::TEXTURE_2D, id_diff);

			gl::BindVertexArray(meshGL.VAO);
			gl::DrawElements(gl::TRIANGLES, meshGL.size, gl::UNSIGNED_INT, 0);
			gl::BindVertexArray(0);
		}
		shader.stop();

		window.display();
	}



	std::cout << "-----END------\n";

	//unload_model_OGL(name);
	//unload_model(name);

	std::cout << "-----RETURN------\n";
	return 0;
}
