#pragma once

#include "Tower.hpp"

#include <glm/vec2.hpp>

class TowerEntity {
public:
    TowerEntity();
    TowerEntity(const Tower* Tower);
    TowerEntity(const Tower* Tower, const glm::vec2& coord);
    ~TowerEntity();
    TowerEntity(const TowerEntity& other);
    TowerEntity(TowerEntity&& other);
    TowerEntity& operator=(const TowerEntity& other);
    TowerEntity& operator=(TowerEntity&& other);

    void init(const Tower* Tower);
    void init(const Tower* Tower, const glm::vec2& coord);

    inline float getReloadTimer() const;
    inline void setReloadTimer(float value);
    inline void difReloadTimer(float diff);
    inline void Reload();
    inline void Unload();

    inline unsigned int getNumShells() const;
    inline void setNumShells(unsigned int n);
    inline void incNumShells();
    inline void redNumShells();

    inline glm::vec2 getCoordinate() const;
    inline void setCoordinate(const glm::vec2& coord);

    inline const Tower* getTower() const;

private:
    const Tower* tower;
    float reload_timer;
    unsigned int shells_launched;
    glm::vec2 coordinate;
};

inline glm::vec2 TowerEntity::getCoordinate() const
{
    return coordinate;
}

inline void TowerEntity::setCoordinate(const glm::vec2& coord)
{
    coordinate = coord;
}

inline float TowerEntity::getReloadTimer() const
{
    return reload_timer;
}

inline void TowerEntity::setReloadTimer(float value)
{
    reload_timer = value;
}

inline void TowerEntity::difReloadTimer(float diff)
{
    reload_timer += diff;
}

inline void TowerEntity::Reload()
{
    reload_timer = 0;
}

inline void TowerEntity::Unload()
{
    reload_timer = tower->getPropsT().getReloadTime();
}

inline unsigned int TowerEntity::getNumShells() const
{
    return shells_launched;
}

inline void TowerEntity::setNumShells(unsigned int n)
{
    shells_launched = n;
}

inline void TowerEntity::incNumShells()
{
    shells_launched++;
}

inline void TowerEntity::redNumShells()
{
    shells_launched--;
}

inline const Tower* TowerEntity::getTower() const
{
    return tower;
}
