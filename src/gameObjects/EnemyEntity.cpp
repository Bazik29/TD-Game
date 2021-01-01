#include "EnemyEntity.hpp"

#include <stdexcept>

EnemyEntity::EnemyEntity()
{
    enemy = nullptr;
    current_hp = 0;
    haunt_shells = 0;
    way_point = 0;
    coordinate = glm::vec2(0.0f);
}

EnemyEntity::EnemyEntity(const Enemy* enemy)
{
    if (!enemy)
        throw std::invalid_argument("EnemyEntity: Enemy* is null");
        
    this->enemy = enemy;
    current_hp = enemy->getProps().getMaxHP();
    haunt_shells = 0;
    way_point = 0;
    coordinate = glm::vec2(0.0f);
}

EnemyEntity::EnemyEntity(const Enemy* enemy, const glm::vec2& coord)
{
    if (!enemy)
        throw std::invalid_argument("EnemyEntity: Enemy* is null");

    this->enemy = enemy;
    current_hp = enemy->getProps().getMaxHP();
    coordinate = coord;
    haunt_shells = 0;
    way_point = 0;
}

void EnemyEntity::init(const Enemy* enemy)
{
    if (!enemy)
        throw std::invalid_argument("EnemyEntity: Enemy* is null");

    this->enemy = enemy;
    current_hp = enemy->getProps().getMaxHP();
    haunt_shells = 0;
    way_point = 0;
    coordinate = glm::vec2(0.0f);
}

void EnemyEntity::init(const Enemy* enemy, const glm::vec2& coord)
{
    if (!enemy)
        throw std::invalid_argument("EnemyEntity: Enemy* is null");

    this->enemy = enemy;
    current_hp = enemy->getProps().getMaxHP();
    coordinate = coord;
    haunt_shells = 0;
    way_point = 0;
}

EnemyEntity::~EnemyEntity()
{
}
