#pragma once
#include <gl_core_4_3.hpp>

#include "GLSLProgram.hpp"
#include <glm/matrix.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <cmath>

#include "../gameObjects/EnemyEntity.hpp"
#include <list>

class Renderer {
public:
    Renderer();
    ~Renderer();
    void draw(const std::list<EnemyEntity>& enemies);

private:
    GLSLProgram shader;

    glm::mat4 view;
    glm::mat4 projection;
};
