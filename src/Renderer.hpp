#pragma once
#include <gl_core_4_3.hpp>

#include "GLSLProgram.hpp"
#include <glm/matrix.hpp>

#include "../gameObjects/Level.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();
    void draw(const Level& level);

private:
    GLSLProgram shader;

    glm::mat4 view;
    glm::mat4 projection;

    void draw(const std::list<EnemyEntity>& enemies);
};
