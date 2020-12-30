#pragma once

#include <glm/vec2.hpp>

#include "Enemy.hpp"

struct EnemyEntity {
    const Enemy* enemy;
    int current_hp;
    int haunt_shells;
    unsigned int way_point;
    glm::vec2 coordinate;
};

// TODO move
