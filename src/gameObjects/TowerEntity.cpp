#include "TowerEntity.hpp"

#include <stdexcept>

TowerEntity::TowerEntity()
{
    tower = nullptr;
    reload_timer = 0.0f;
    shells_launched = 0;
    coordinate = glm::vec2(0.0f);
}

TowerEntity::TowerEntity(const Tower* tower)
{
    init(tower);
}

TowerEntity::TowerEntity(const Tower* tower, const glm::vec2& coord)
{
    init(tower, coord);
}

void TowerEntity::init(const Tower* tower)
{
    if (!tower)
        throw std::invalid_argument("TowerEntity: Tower* is null");

    this->tower = nullptr;
    reload_timer = 0.0f;
    shells_launched = 0;
    coordinate = glm::vec2(0.0f);
}

void TowerEntity::init(const Tower* tower, const glm::vec2& coord)
{
    if (!tower)
        throw std::invalid_argument("TowerEntity: Tower* is null");
    this->tower = tower;
    reload_timer = 0.0f;
    shells_launched = 0;
    coordinate = coord;
}

TowerEntity::~TowerEntity()
{
}
