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

    if (!tower)
        throw std::invalid_argument("TowerEntity: Tower* is null");

    this->tower = tower;
    reload_timer = 0.0f;
    shells_launched = 0;
    coordinate = glm::vec2(0.0f);
}

TowerEntity::TowerEntity(const Tower* tower, const glm::vec2& coord)
{
    if (!tower)
        throw std::invalid_argument("TowerEntity: Tower* is null");

    this->tower = tower;
    reload_timer = 0.0f;
    shells_launched = 0;
    coordinate = coord;
}

void TowerEntity::init(const Tower* tower)
{
    if (!tower)
        throw std::invalid_argument("TowerEntity: Tower* is null");

    this->tower = tower;
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

TowerEntity::TowerEntity(const TowerEntity& other)
{
    this->tower = other.tower;
    this->reload_timer = other.reload_timer;
    this->shells_launched = other.shells_launched;
    this->coordinate = other.coordinate;
}

TowerEntity::TowerEntity(TowerEntity&& other)
{
    this->tower = other.tower;
    this->reload_timer = other.reload_timer;
    this->shells_launched = other.shells_launched;
    this->coordinate = other.coordinate;
}

TowerEntity& TowerEntity::operator=(const TowerEntity& other)
{
    this->tower = other.tower;
    this->reload_timer = other.reload_timer;
    this->shells_launched = other.shells_launched;
    this->coordinate = other.coordinate;
    return *this;
}

TowerEntity& TowerEntity::operator=(TowerEntity&& other)
{
    this->tower = other.tower;
    this->reload_timer = other.reload_timer;
    this->shells_launched = other.shells_launched;
    this->coordinate = other.coordinate;
    return *this;
}
