#pragma once

#include "ShellProperty.hpp"

class TowerProperty {
public:
    TowerProperty();
    TowerProperty(float attack_radius,
        unsigned int damage,
        float reload_time,
        const glm::vec4& color);
    ~TowerProperty();
    TowerProperty(const TowerProperty& other) = default;
    TowerProperty(TowerProperty&& other) = default;
    TowerProperty& operator=(const TowerProperty& other) = default;
    TowerProperty& operator=(TowerProperty&& other) = default;

    void init(float attack_radius,
        unsigned int damage,
        float reload_time,
        const glm::vec4& color);

    inline float getReloadTime() const;
    inline void setReloadTime(float time);
    inline unsigned int getDamage() const;
    inline void setDamage(unsigned int damage);
    inline float getAttackRadius() const;
    inline void setAttackRadius(float attack_radius);

    inline glm::vec4 getColor() const;
    inline void getColor(const glm::vec4& color);

private:
    float attack_radius;
    unsigned int damage;
    float reload_time;
    glm::vec4 color;
};

inline float TowerProperty::getReloadTime() const
{
    return reload_time;
}

inline void TowerProperty::setReloadTime(float time)
{
    reload_time = time;
}

inline unsigned int TowerProperty::getDamage() const
{
    return damage;
}

inline void TowerProperty::setDamage(unsigned int damage)
{
    this->damage = damage;
}

inline float TowerProperty::getAttackRadius() const
{
    return attack_radius;
}

inline void TowerProperty::setAttackRadius(float attack_radius)
{
    this->attack_radius = attack_radius;
}

inline glm::vec4 TowerProperty::getColor() const
{
    return color;
}

inline void TowerProperty::getColor(const glm::vec4& color)
{
    this->color = color;
}
