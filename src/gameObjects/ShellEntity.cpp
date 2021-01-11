#include "ShellEntity.hpp"

ShellEntity::ShellEntity()
{
    tower = nullptr;
    enemy = nullptr;
    coordinate = glm::vec2(0.0f, 0.0f);
    angle = 0;
}

ShellEntity::ShellEntity(const TowerEntity* tower, EnemyEntity* enemy)
{
    this->tower = tower;
    this->enemy = enemy;
    coordinate = tower->getCoordinate();
    angle = 0;
}

ShellEntity::~ShellEntity()
{
}

ShellEntity::ShellEntity(const ShellEntity& other)
{
    tower = other.tower;
    enemy = other.enemy;
    coordinate = other.coordinate;
    angle = other.angle;
}

ShellEntity::ShellEntity(ShellEntity&& other)
{
    tower = other.tower;
    enemy = other.enemy;
    coordinate = other.coordinate;
    angle = other.angle;
}

ShellEntity& ShellEntity::operator=(const ShellEntity& other)
{
    tower = other.tower;
    enemy = other.enemy;
    coordinate = other.coordinate;
    angle = other.angle;

    return *this;
}

ShellEntity& ShellEntity::operator=(ShellEntity&& other)
{
    tower = other.tower;
    enemy = other.enemy;
    coordinate = other.coordinate;
    angle = other.angle;

    return *this;
}
