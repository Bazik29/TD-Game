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

ShellEntity::ShellEntity(const ShellEntity& other)
{
    this->tower = other.tower;
    this->enemy = other.enemy;
    coordinate = other.coordinate;
}

ShellEntity::ShellEntity(ShellEntity&& other)
{
    this->tower = other.tower;
    this->enemy = other.enemy;
    coordinate = other.coordinate;
}

ShellEntity& ShellEntity::operator=(const ShellEntity& other)
{
    this->tower = other.tower;
    this->enemy = other.enemy;
    coordinate = other.coordinate;

    return *this;
}

ShellEntity& ShellEntity::operator=(ShellEntity&& other)
{
    this->tower = other.tower;
    this->enemy = other.enemy;
    coordinate = other.coordinate;

    return *this;
}
