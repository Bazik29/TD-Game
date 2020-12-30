#pragma once
#include <glm/vec2.hpp>

#include "Tower.hpp"

struct TowerEntity
{
    const Tower* tower;
    float cooldown_timer;
    unsigned int shells_launched;
    glm::vec2 coordinate;
};
