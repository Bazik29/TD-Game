#pragma once

#include <glm/vec4.hpp>

#include "MeshGL.hpp"

struct Enemy {
    unsigned int hp;
    float speed;
    unsigned int damage;
    MeshGL* meshGL;
    glm::vec4 color;
};
