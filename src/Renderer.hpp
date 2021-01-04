#pragma once
#include <gl_core_4_3.hpp>

#include "GLSLProgram.hpp"
#include <glm/matrix.hpp>

#include "../gameObjects/Level.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init();

    inline void setViewMatrix(const glm::mat4 view);
    inline void setProjectionMatrix(const glm::mat4 projection);

    void draw(const Level* level);
    void drawTowerForBuilding(const TowerEntity* tower);

private:
    GLSLProgram shader;
    GLSLProgram shader_grid;

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 pv_matrix;

    void draw(const std::list<ShellEntity>& launched_shells);
    void draw(const std::list<EnemyEntity>& enemies);
    void draw(const LevelTowerEStorage& towers);
    void draw(const BattleGridEntity& grid);
};

inline void Renderer::setViewMatrix(const glm::mat4 view)
{
    this->view = view;
    pv_matrix = projection * view;
}

inline void Renderer::setProjectionMatrix(const glm::mat4 projection)
{
    this->projection = projection;
    pv_matrix = projection * view;
}
