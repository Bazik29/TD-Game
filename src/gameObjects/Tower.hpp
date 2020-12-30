#pragma once

#include <glm/vec4.hpp>

#include "MeshGL.hpp"

struct Shell {
    float speed;
    MeshGL* meshGL;
    glm::vec4 color;
};

struct Tower {
    float radius;
    unsigned int damage;
    float cooldown_time;
    MeshGL* meshGL;
    glm::vec4 color;

    Shell shell;
};
