#include "Renderer.hpp"

#include <gl_core_4_3.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

Renderer::Renderer()
    : view(1.f)
    , projection(1.f)
{
    pv_matrix = projection * view;
}

Renderer::~Renderer() { }

void Renderer::init()
{
    // Enemy and Tower shader
    shader.attach(fs::path("../../shaders/simple.vert"));
    shader.attach(fs::path("../../shaders/simple.frag"));
    shader.link();

    shader.addUniformLocation("color");
    shader.addUniformLocation("PVM");

    // Battle grid shader
    shader_grid.attach(fs::path("../../shaders/grid.vert"));
    shader_grid.attach(fs::path("../../shaders/grid.geom"));
    shader_grid.attach(fs::path("../../shaders/grid.frag"));
    shader_grid.link();

    shader_grid.addUniformLocation("PVM");
    shader_grid.addUniformLocation("coeff");

    shader_grid.start();
    shader_grid.setUniform("coeff", 1.0f);
    shader_grid.stop();
}

void Renderer::draw(const Level* level)
{
    draw(level->battle_grid_entity);
    draw(level->spawned_enemies);
    
    draw(level->built_towers);
    draw(level->shells);
}

void Renderer::draw(const std::list<ShellEntity>& shells) 
{
        for (auto& shell : shells) {
        auto coord = shell.getCoordinate();
        auto vao = shell.getMesh()->getVAO();
        auto size = shell.getMesh()->getSize();
        auto color = shell.getProps().getColor();

        glm::mat4 PVM = pv_matrix * glm::translate(glm::mat4(1.0f), glm::vec3(coord, 0.0f));

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

void Renderer::draw(const std::list<EnemyEntity>& enemies)
{
    for (auto& en : enemies) {
        auto coord = en.getCoordinate();
        auto vao = en.getEnemy()->getMesh()->getVAO();
        auto size = en.getEnemy()->getMesh()->getSize();
        auto color = en.getEnemy()->getProps().getColor();

        glm::mat4 PVM = pv_matrix * glm::translate(glm::mat4(1.0f), glm::vec3(coord, 0.0f));

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

void Renderer::draw(const std::vector<TowerEntity>& towers)
{
    for (auto& tower : towers) {
        auto coord = tower.getCoordinate();
        auto vao = tower.getTower()->getMeshT()->getVAO();
        auto size = tower.getTower()->getMeshT()->getSize();
        auto color = tower.getTower()->getPropsT().getColor();

        glm::mat4 PVM = pv_matrix * glm::translate(glm::mat4(1.0f), glm::vec3(coord, 0.0f));

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
    shader_grid.setUniform("PVM", pv_matrix);

    gl::BindVertexArray(grid.mesh().getVAO());
    gl::EnableVertexAttribArray(0);
    gl::EnableVertexAttribArray(1);
    gl::DrawArrays(gl::POINTS, 0, grid.mesh().getSize());

    gl::BindVertexArray(0);

    shader_grid.stop();
}

void Renderer::drawTowerForBuilding(const TowerEntity* tower)
{
    auto coord = tower->getCoordinate();
    auto vao = tower->getTower()->getMeshT()->getVAO();
    auto size = tower->getTower()->getMeshT()->getSize();
    auto color = tower->getTower()->getPropsT().getColor();
    color.a = 0.2;

    glm::mat4 PVM = pv_matrix * glm::translate(glm::mat4(1.0f), glm::vec3(coord, 0.0f));

    shader.start();
    shader.setUniform("color", color);
    shader.setUniform("PVM", PVM);

    gl::BindVertexArray(vao);
    gl::EnableVertexAttribArray(0);
    gl::DrawElements(gl::TRIANGLES, size, gl::UNSIGNED_INT, 0);
    gl::BindVertexArray(0);

    shader.stop();
}
