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
    draw(level->launched_shells);
}

void Renderer::draw(const std::list<ShellEntity>& launched_shells)
{
    for (auto shell_it = launched_shells.begin(); shell_it != launched_shells.end(); shell_it++) {
        GLuint vao = shell_it->getMesh()->getVAO();
        unsigned int size = shell_it->getMesh()->getSize();

        const auto& coord = shell_it->getCoordinate();
        const auto& color = shell_it->getProps().getColor();

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
    for (auto& enemy : enemies) {
        GLuint vao = enemy.getEnemy()->getMesh()->getVAO();
        unsigned int size = enemy.getEnemy()->getMesh()->getSize();

        const auto& coord = enemy.getCoordinate();
        const auto& color = enemy.getEnemy()->getProps().getColor();

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

void Renderer::draw(const LevelTowerEStorage& towers)
{
    for (auto& tower : towers) {
        GLuint vao = tower.getTower()->getMeshT()->getVAO();
        unsigned int size = tower.getTower()->getMeshT()->getSize();

        const auto& coord = tower.getCoordinate();
        const auto& color = tower.getTower()->getPropsT().getColor();

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
    GLuint vao = grid.mesh().getVAO();
    unsigned int size = grid.mesh().getSize();

    shader_grid.start();
    shader_grid.setUniform("PVM", pv_matrix);

    gl::BindVertexArray(vao);
    gl::EnableVertexAttribArray(0);
    gl::EnableVertexAttribArray(1);
    gl::DrawArrays(gl::POINTS, 0, size);

    gl::BindVertexArray(0);

    shader_grid.stop();
}

void Renderer::drawTowerForBuilding(const TowerEntity* tower)
{
    GLuint vao = tower->getTower()->getMeshT()->getVAO();
    unsigned int size = tower->getTower()->getMeshT()->getSize();

    auto color = tower->getTower()->getPropsT().getColor();
    const auto& coord = tower->getCoordinate();
    color.a = 0.7;

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
