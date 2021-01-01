#include "EnemyProperty.hpp"

EnemyProperty::EnemyProperty()
{
    hp = 0;
    speed = 0;
    damage = 0;
    color = glm::vec4(1.0f);
}

EnemyProperty::EnemyProperty(unsigned int hp, float speed, unsigned int damage, const glm::vec4& color)
{
    init(hp, speed, damage, color);
}

void EnemyProperty::init(unsigned int hp, float speed, unsigned int damage, const glm::vec4& color)
{
    this->hp = hp;
    this->speed = speed;
    this->damage = damage;
    this->color = color;
}

EnemyProperty::~EnemyProperty()
{
}
