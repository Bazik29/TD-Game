#pragma once

#include <glm/vec4.hpp>

class EnemyProperty {
public:
    EnemyProperty();
    EnemyProperty(unsigned int hp,
        float speed,
        unsigned int damage,
        const glm::vec4& color);
    ~EnemyProperty();
    EnemyProperty(const EnemyProperty& other) = default;
    EnemyProperty(EnemyProperty&& other) = default;
    EnemyProperty& operator=(const EnemyProperty& other) = default;
    EnemyProperty& operator=(EnemyProperty&& other) = default;

    void init(unsigned int hp,
        float speed,
        unsigned int damage,
        const glm::vec4& color);

    inline unsigned int getMaxHP() const;
    inline void setMaxHP(unsigned int hp);
    inline float getSpeed() const;
    inline void setSpeed(float speed);
    inline unsigned int getDamage() const;
    inline void setDamage(unsigned int damage);
    inline glm::vec4 getColor() const;
    inline void setColor(const glm::vec4& color);

private:
    unsigned int hp;
    float speed;
    unsigned int damage;
    glm::vec4 color;
};

inline unsigned int EnemyProperty::getMaxHP() const
{
    return hp;
}

inline void EnemyProperty::setMaxHP(unsigned int hp)
{
    this->hp = hp;
}

inline float EnemyProperty::getSpeed() const
{
    return speed;
}

inline void EnemyProperty::setSpeed(float speed)
{
    this->speed = speed;
}

inline unsigned int EnemyProperty::getDamage() const
{
    return damage;
}

inline void EnemyProperty::setDamage(unsigned int damage)
{
    this->damage = damage;
}

inline glm::vec4 EnemyProperty::getColor() const
{
    return color;
}

inline void EnemyProperty::setColor(const glm::vec4& color)
{
    this->color = color;
}
