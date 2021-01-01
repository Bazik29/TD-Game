#pragma once

#include "../logicObjects/EnemyProperty.hpp"
#include "../renderObjects/ElementsMeshGl.hpp"

#include <glm/vec4.hpp>

class Enemy {
public:
    Enemy();
    Enemy(const EnemyProperty& property, const ElementsMeshGl* mesh);
    ~Enemy();
    Enemy(const Enemy& other) = default;
    Enemy(Enemy&& other) = default;
    Enemy& operator=(const Enemy& other) = default;
    Enemy& operator=(Enemy&& other) = default;

    void init(const EnemyProperty& property, const ElementsMeshGl* mesh);

    inline const EnemyProperty& getProps() const;
    inline const ElementsMeshGl* getMesh() const;

private:
    EnemyProperty property;
    const ElementsMeshGl* mesh;
};

inline const EnemyProperty& Enemy::getProps() const
{
    return property;
}

inline const ElementsMeshGl* Enemy::getMesh() const
{
    return mesh;
}
