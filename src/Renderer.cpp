#include "Renderer.hpp"

#include <gl_core_4_3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


Renderer::Renderer()
{
    shader.attach(fs::path("../../shaders/simple.vert"));
    shader.attach(fs::path("../../shaders/simple.frag"));
    shader.link();

    shader.addUniformLocation("color");
    shader.addUniformLocation("PVM");

    projection = glm::perspective(45.0f, 640.f / 480, 0.1f, 100.0f);
    view = glm::lookAt(
        glm::vec3(12.5f, 10.5f, 21.0f),
        glm::vec3(12.5f, 10.5f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    shader_grid.attach(fs::path("../../shaders/grid.vert"));
    shader_grid.attach(fs::path("../../shaders/grid.geom"));
    shader_grid.attach(fs::path("../../shaders/grid.frag"));
    shader_grid.link();

    shader_grid.addUniformLocation("PVM");
    shader_grid.addUniformLocation("coeff");

    shader_grid.start();
    shader_grid.setUniform("PVM", projection * view);
    shader_grid.setUniform("coeff", 2.0f);
    shader_grid.stop();

    gl::GenVertexArrays(1, &VAO);
    gl::BindVertexArray(VAO);
    gl::GenBuffers(1, &VBO);
    gl::BindBuffer(gl::ARRAY_BUFFER, VBO);
    gl::BufferData(gl::ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], gl::STATIC_DRAW);
    gl::VertexAttribPointer(0, 2, gl::FLOAT, gl::FALSE_, sizeof(glm::vec2), (void*)0);
    gl::BindBuffer(gl::ARRAY_BUFFER, VBO_C);
    gl::BufferData(gl::ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], gl::DYNAMIC_DRAW);
    gl::VertexAttribPointer(1, 4, gl::FLOAT, gl::FALSE_, 4 * sizeof(float), (void*)0);
    gl::BindVertexArray(0);
}

Renderer::~Renderer() { }

void Renderer::draw(const Level& level)
{
    draw(level.battle_grid_entity);
    draw(level.spawned_enemies);
}

void Renderer::draw(const std::list<EnemyEntity>& enemies)
{
    for (auto& en : enemies) {
        glm::mat4 PVM = projection * view * glm::translate(glm::mat4(1.0f), glm::vec3(en.getCoordinate(), 0.0f));

        auto vao = en.getEnemy()->getMesh()->getVAO();
        auto size = en.getEnemy()->getMesh()->getSize();
        auto color = en.getEnemy()->getProps().getColor();
        
        shader.start();
        shader.setUniform("color", color);
        shader.setUniform("PVM", PVM);

        gl::BindVertexArray(vao);
        gl::EnableVertexAttribArray(0);
        gl::DrawElements(gl::TRIANGLES, size, gl::UNSIGNED_INT, 0);
        gl::BindVertexArray(0);

        shader.stop();
    }
}

void Renderer::draw(const BattleGridEntity& grid)
{
    shader_grid.start();

    gl::BindVertexArray(grid.mesh().getVAO());
    gl::EnableVertexAttribArray(0);
    gl::EnableVertexAttribArray(1);
    gl::DrawArrays(gl::POINTS, 0, grid.mesh().getSize());

    gl::BindVertexArray(0);

    shader_grid.stop();
}
