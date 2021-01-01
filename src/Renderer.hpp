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
    GLSLProgram shader_grid;

    glm::mat4 view;
    glm::mat4 projection;

    void draw(const std::list<EnemyEntity>& enemies);
    void draw(const BattleGridEntity& grid);

        std::vector<glm::vec2> vertices = {
        { 0.0, 0.0 },
        { 0.0, 2 },
        { 0.0, 4 },
        { 2, 0.0 },
        { 2, 2 },
        { 2, 4 },
        { 4, 0.0 },
        { 4, 2 },
        { 4, 4 }
    };
    std::vector<float> colors = {
        1.0,
        1.0,
        0.0,
        1.0,
        1.0,
        0.0,
        0.0,
        1.0,
        1.0,
        0.0,
        1.0,
        1.0,
        1.0,
        0.0,
        0.0,
        1.0,
        0.0,
        1.0,
        0.0,
        1.0,
        0.0,
        1.0,
        1.0,
        1.0,
        1.0,
        0.0,
        1.0,
        1.0,
        1.0,
        1.0,
        1.0,
        1.0,
        1.0,
        1.0,
        0.0,
        1.0,
    };

    GLuint VAO, VBO, EBO, VBO_C;
};
