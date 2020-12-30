#include "Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

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
        glm::vec3(12.0f, 10.0f, 17.0f),
        glm::vec3(12.0f, 10.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    shader.start();
    shader.setUniform("view", view);
    shader.setUniform("projection", projection);
    shader.stop();
}

Renderer::~Renderer() { }

void Renderer::draw(const Level& level) 
{
    draw(level.spawned_enemies);
}

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
