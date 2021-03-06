#pragma once

#include "EnemyEntity.hpp"
#include "TowerEntity.hpp"
#include <glm/vec3.hpp>

class ShellEntity {
public:
    ShellEntity();
    ShellEntity(const TowerEntity* tower, EnemyEntity* enemy);

    ~ShellEntity();
    ShellEntity(const ShellEntity& other);
    ShellEntity(ShellEntity&& other);
    ShellEntity& operator=(const ShellEntity& other);
    ShellEntity& operator=(ShellEntity&& other);

    inline const TowerEntity* getTowerE() const;
    inline EnemyEntity* getEnemyE() const;

    inline const ShellProperty& getProps() const;
    inline const ElementsMeshGl* getMesh() const;

    inline const glm::vec2& getCoordinate() const;
    inline void move(const glm::vec2& delta);

    inline void setAngle(const float& ang);
    inline const float& getAngle() const;

private:
    const TowerEntity* tower;
    EnemyEntity* enemy;

    glm::vec2 coordinate;
    float angle;
};

inline const TowerEntity* ShellEntity::getTowerE() const
{
    return tower;
}

inline EnemyEntity* ShellEntity::getEnemyE() const
{
    return enemy;
}

inline const ShellProperty& ShellEntity::getProps() const
{
    return tower->getTower()->getPropsS();
}

inline const ElementsMeshGl* ShellEntity::getMesh() const
{
    return tower->getTower()->getMeshS();
}

inline const glm::vec2& ShellEntity::getCoordinate() const
{
    return coordinate;
}

inline void ShellEntity::move(const glm::vec2& delta)
{
    coordinate += delta;
}

inline void ShellEntity::setAngle(const float& ang) 
{
    angle = ang;
}

inline const float& ShellEntity::getAngle() const
{
    return angle;
}
