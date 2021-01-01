#pragma once

#include "Enemy.hpp"

#include <glm/vec2.hpp>

class EnemyEntity {
public:
    EnemyEntity();
    EnemyEntity(const Enemy* enemy);
    EnemyEntity(const Enemy* enemy, const glm::vec2& coord);
    ~EnemyEntity();
    EnemyEntity(const EnemyEntity& other) = default;
    EnemyEntity(EnemyEntity&& other) = default;
    EnemyEntity& operator=(const EnemyEntity& other) = default;
    EnemyEntity& operator=(EnemyEntity&& other) = default;

    void init(const Enemy* enemy);
    void init(const Enemy* enemy, const glm::vec2& coord);

    inline int getHP() const;
    inline void setHP(int hp);
    inline void difHP(int diff);

    inline int getHauntShells() const;
    inline void setHauntShells(int shells);
    inline void incHauntShells();
    inline void redHauttSheels();

    inline unsigned int getWayPoint() const;
    inline void setWayPoint(unsigned int point);
    inline void incWayPoint();
    inline void redWayPoint();

    inline glm::vec2 getCoordinate() const;
    inline void setCoordinate(const glm::vec2& coord);

    inline void move(const glm::vec2& delta);

    inline const Enemy* getEnemy() const;

private:
    int current_hp;
    int haunt_shells;
    unsigned int way_point;
    glm::vec2 coordinate;
    const Enemy* enemy;
};

inline int EnemyEntity::getHP() const
{
    return current_hp;
}

inline void EnemyEntity::setHP(int hp)
{
    current_hp = hp;
}

inline void EnemyEntity::difHP(int diff)
{
    current_hp += diff;
}

inline int EnemyEntity::getHauntShells() const
{
    return haunt_shells;
}

inline void EnemyEntity::setHauntShells(int shells)
{
    haunt_shells = shells;
}

inline void EnemyEntity::incHauntShells()
{
    haunt_shells++;
}

inline void EnemyEntity::redHauttSheels()
{
    haunt_shells--;
}

inline unsigned int EnemyEntity::getWayPoint() const
{
    return way_point;
}

inline void EnemyEntity::setWayPoint(unsigned int point)
{
    way_point = point;
}

inline void EnemyEntity::incWayPoint()
{
    way_point++;
}

inline void EnemyEntity::redWayPoint()
{
    way_point--;
}

inline glm::vec2 EnemyEntity::getCoordinate() const
{
    return coordinate;
}

inline void EnemyEntity::setCoordinate(const glm::vec2& coord)
{
    coordinate = coord;
}

inline void EnemyEntity::move(const glm::vec2& delta)
{
    coordinate += delta;
}

inline const Enemy* EnemyEntity::getEnemy() const
{
    return enemy;
}
