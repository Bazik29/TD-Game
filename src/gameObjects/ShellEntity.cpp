#include "ShellEntity.hpp"

ShellEntity::ShellEntity()
{
    tower = nullptr;
    enemy = nullptr;
    coordinate = glm::vec2(0.0f, 0.0f);
}

ShellEntity::ShellEntity(const TowerEntity* tower, EnemyEntity* enemy)
{
    this->tower = tower;
    this->enemy = enemy;
    coordinate = tower->getCoordinate();
}

ShellEntity::~ShellEntity()
{
}
