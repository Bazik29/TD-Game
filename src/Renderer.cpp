#include "Renderer.hpp"

// void makePolyhedron(std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices, float r = 1, int n = 8)
// {
// 	double pi = std::acos(-1);
// 	float angle = 2 * pi / n;

// 	vertices.push_back(glm::vec2(0, 0));
// 	for (size_t i = 0; i < n; i++)
// 	{
// 		vertices.push_back(glm::vec2(r * std::cos(i * angle), r * std::sin(i * angle)));

// 		int a = i + 1;
// 		int b = i + 2;
// 		if (b > n)
// 		{
// 			b = 1;
// 		}

// 		if (i % 2 == 0)
// 		{
// 			indices.push_back(0);
// 			indices.push_back(a);
// 			indices.push_back(b);
// 		} else
// 		{
// 			indices.push_back(a);
// 			indices.push_back(b);
// 			indices.push_back(0);
// 		}
// 	}
// }

// void makeArrow(std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices, float r = 1)
// {
// 	vertices.push_back(glm::vec2(0, r));
// 	vertices.push_back(glm::vec2(r, -r));
// 	vertices.push_back(glm::vec2(0, -r / 2.f));
// 	vertices.push_back(glm::vec2(-r, -r));

// 	indices.push_back(0);
// 	indices.push_back(1);
// 	indices.push_back(2);
// 	indices.push_back(2);
// 	indices.push_back(3);
// 	indices.push_back(0);
// }

Renderer::Renderer()
{
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
        glm::vec3(0.0f, 1.0f, 0.0f));

    shader.start();
    shader.setUniform("view", view);
    shader.setUniform("projection", projection);
    shader.stop();
}

Renderer::~Renderer() { }

void Renderer::draw(const std::list<EnemyEntity>& enemies)
{
    for (auto& en : enemies) {
        shader.start();
        shader.setUniform("color", en.enemy->color);
        shader.setUniform("model", glm::translate(glm::mat4(1.0f), glm::vec3(en.coordinate, 0.0f)));

        gl::BindVertexArray(en.enemy->meshGL->getVAO());
        gl::DrawElements(gl::TRIANGLES, en.enemy->meshGL->getSize(), gl::UNSIGNED_INT, 0);
        gl::BindVertexArray(0);

        shader.stop();
    }
}

// void Renderer::draw(std::list<Tower>& towers)
// {
// 	//gl::Enable(gl::DEPTH_TEST);

// 	for (auto& en : towers)
// 	{
// 		shader.start();
// 		shader.setUniform("color", colorT.r, colorT.g, colorT.b);
// 		shader.setUniform("view", view);
// 		shader.setUniform("projection", projection);
// 		shader.setUniform("model", glm::translate(glm::mat4(1.0f), glm::vec3(en.coordinate, 0.0f)));

// 		gl::BindVertexArray(tower.VAO);
// 		gl::DrawElements(gl::TRIANGLES, tower.size, gl::UNSIGNED_INT, 0);
// 		gl::BindVertexArray(0);

// 		shader.stop();
// 	}
// }

// void Renderer::draw(std::list<Shell>& shells)
// {
// 	//gl::Enable(gl::DEPTH_TEST);

// 	for (auto& en : shells)
// 	{
// 		shader.start();
// 		shader.setUniform("color", colorT.r, colorT.g, colorT.b);
// 		shader.setUniform("view", view);
// 		shader.setUniform("projection", projection);
// 		shader.setUniform("model", glm::translate(glm::mat4(1.0f), glm::vec3(en.coordinate, 0.0f)));

// 		gl::BindVertexArray(shell.VAO);
// 		gl::DrawElements(gl::TRIANGLES, shell.size, gl::UNSIGNED_INT, 0);
// 		gl::BindVertexArray(0);

// 		shader.stop();
// 	}
// }
