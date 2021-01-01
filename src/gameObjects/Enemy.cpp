#include "Enemy.hpp"

Enemy::Enemy()
    : property()
{
    mesh = nullptr;
}

Enemy::Enemy(const EnemyProperty& property, const ElementsMeshGl* mesh)
{
    init(property, mesh);
}

void Enemy::init(const EnemyProperty& property, const ElementsMeshGl* mesh)
{
    this->property = property;
    this->mesh = mesh;
}

Enemy::~Enemy()
{
}
