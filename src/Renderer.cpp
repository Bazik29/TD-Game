#include "Renderer.hpp"

void makePolyhedron(std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices, float r = 1, int n = 8)
{
	double pi = std::acos(-1);
	float angle = 2 * pi / n;

	vertices.push_back(glm::vec2(0, 0));
	for (size_t i = 0; i < n; i++)
	{
		vertices.push_back(glm::vec2(r * std::cos(i * angle), r * std::sin(i * angle)));

		int a = i + 1;
		int b = i + 2;
		if (b > n)
		{
			b = 1;
		}

		if (i % 2 == 0)
		{
			indices.push_back(0);
			indices.push_back(a);
			indices.push_back(b);
		} else
		{
			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(0);
		}
	}
}

void makeSquare(std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices, float r = 1)
{
	vertices.push_back(glm::vec2(-r, r));
	vertices.push_back(glm::vec2(r, r));
	vertices.push_back(glm::vec2(r, -r));
	vertices.push_back(glm::vec2(-r, -r));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);
}

void makeArrow(std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices, float r = 1)
{
	vertices.push_back(glm::vec2(0, r));
	vertices.push_back(glm::vec2(r, -r));
	vertices.push_back(glm::vec2(0, -r / 2.f));
	vertices.push_back(glm::vec2(-r, -r));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);
}

MeshGL load_mesh_OGL(std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices)
{
	MeshGL meshGL;

	meshGL.size = indices.size();

	gl::GenVertexArrays(1, &meshGL.VAO);
	gl::GenBuffers(1, &meshGL.VBO);
	gl::GenBuffers(1, &meshGL.EBO);

	gl::BindVertexArray(meshGL.VAO);

	gl::BindBuffer(gl::ARRAY_BUFFER, meshGL.VBO);
	gl::BufferData(gl::ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], gl::STATIC_DRAW);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, meshGL.EBO);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], gl::STATIC_DRAW);

	// vertex positions
	gl::EnableVertexAttribArray(0);
	gl::VertexAttribPointer(0, 2, gl::FLOAT, gl::FALSE_, sizeof(glm::vec2), (void*)0);

	gl::BindVertexArray(0);

	return meshGL;
}

Renderer::Renderer()
{
	std::vector<glm::vec2> vertices;
	std::vector<unsigned int> indices;

	makeSquare(vertices, indices, 0.5);
	enemy = load_mesh_OGL(vertices, indices);
	vertices.clear();
	indices.clear();

	makePolyhedron(vertices, indices, 1, 16);
	tower = load_mesh_OGL(vertices, indices);
	vertices.clear();
	indices.clear();

	makeArrow(vertices, indices, 0.5);
	shell = load_mesh_OGL(vertices, indices);
	vertices.clear();
	indices.clear();

	shader.attach(fs::path("../../shaders/simple.vert"));
	shader.attach(fs::path("../../shaders/simple.frag"));
	shader.link();

	shader.addUniformLocation("color");

	shader.addUniformLocation("view");
	shader.addUniformLocation("projection");
	shader.addUniformLocation("model");

	projection = glm::perspective(45.0f, 640.f / 480, 0.1f, 100.0f);
	view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

}

void Renderer::draw(std::list<Enemy>& enemies)
{
	//gl::ClearColor(0, 1, 1, 1);
	//gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	//gl::Enable(gl::DEPTH_TEST);

	for (auto& en : enemies)
	{
		shader.start();
		shader.setUniform("color", colorE.r, colorE.g, colorE.b);
		shader.setUniform("view", view);
		shader.setUniform("projection", projection);
		shader.setUniform("model", glm::translate(glm::mat4(1.0f), glm::vec3(en.coordinate, 0.0f)));


		gl::BindVertexArray(enemy.VAO);
		gl::DrawElements(gl::TRIANGLES, enemy.size, gl::UNSIGNED_INT, 0);
		gl::BindVertexArray(0);

		shader.stop();
	}
}

void Renderer::draw(std::list<Tower>& towers)
{
	//gl::Enable(gl::DEPTH_TEST);

	for (auto& en : towers)
	{
		shader.start();
		shader.setUniform("color", colorT.r, colorT.g, colorT.b);
		shader.setUniform("view", view);
		shader.setUniform("projection", projection);
		shader.setUniform("model", glm::translate(glm::mat4(1.0f), glm::vec3(en.coordinate, 0.0f)));


		gl::BindVertexArray(tower.VAO);
		gl::DrawElements(gl::TRIANGLES, tower.size, gl::UNSIGNED_INT, 0);
		gl::BindVertexArray(0);

		shader.stop();
	}
}

void Renderer::draw(std::list<Shell>& shells)
{
	//gl::Enable(gl::DEPTH_TEST);

	for (auto& en : shells)
	{
		shader.start();
		shader.setUniform("color", colorT.r, colorT.g, colorT.b);
		shader.setUniform("view", view);
		shader.setUniform("projection", projection);
		shader.setUniform("model", glm::translate(glm::mat4(1.0f), glm::vec3(en.coordinate, 0.0f)));


		gl::BindVertexArray(shell.VAO);
		gl::DrawElements(gl::TRIANGLES, shell.size, gl::UNSIGNED_INT, 0);
		gl::BindVertexArray(0);

		shader.stop();
	}
}

Renderer::~Renderer()
{

}
