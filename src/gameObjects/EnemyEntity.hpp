#pragma once

#include <glm/vec2.hpp>

#include "Enemy.hpp"

struct EnemyEntity {
    Enemy* enemy;
    int current_hp;
    int haunt_shells;
    int way_point;
    glm::vec2 coordinate;
};
