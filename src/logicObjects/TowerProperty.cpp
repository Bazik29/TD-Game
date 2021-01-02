#include "TowerProperty.hpp"

TowerProperty::TowerProperty()
{
    attack_radius = 0.0f;
    damage = 0;
    reload_time = 0.0f;
    color = glm::vec4(1.0f);
}

TowerProperty::TowerProperty(float attack_radius,
    unsigned int damage,
    float reload_time,
    const glm::vec4& color)
{
    this->attack_radius = attack_radius;
    this->damage = damage;
    this->reload_time = reload_time;
    this->color = color;
}

void TowerProperty::init(float attack_radius,
    unsigned int damage,
    float reload_time,
    const glm::vec4& color)
{
    this->attack_radius = attack_radius;
    this->damage = damage;
    this->reload_time = reload_time;
    this->color = color;
}

TowerProperty::~TowerProperty()
{
}
