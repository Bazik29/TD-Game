#pragma once

#include "../gameObjects/EnemyEntity.hpp"
#include "../gameObjects/Level.hpp"

#include <glm/vec2.hpp>
#include <list>

class BattleManager {
public:
    BattleManager();
    ~BattleManager();

    inline const Level* getLevel() const;
    inline const TowerEntity* getTowerForBuilding() const;

    void setLevel(Level* level);
    void update(const float& dt, const glm::vec2& cursor);

    void selectedTowerForBuild(const Tower* tower);
    bool tryBuildSelectedTower();
    void discardTowerForBuild();

    void setProjectTower(const Tower* tower);

private:
    Level* level;

    float ENEMY_WAY_BOX = 0.01f;
    float ENEMY_HIT_BOX = 0.01f;

    TowerEntity* tower_for_build = nullptr;
    bool tower_can_build = false;
    glm::vec2 tower_build_coors;

    glm::vec2 cursor;
    glm::uvec2 cursor_grid;
    bool cursor_on_field;

    // auxiliary variables
    float enemy_spawn_timer;
    glm::vec2 enemy_spawn_point;
    glm::vec2 enemy_kill_point;

    void spawnEnemyFromQueue(const float& dt);

    void updateEnemies(const float& dt);
    void towersAttack(const float& dt);

    void updateShells(const float& dt);
    std::list<ShellEntity>::iterator deleteShellt(std::list<ShellEntity>::iterator it);

    void damageTown(unsigned int dmg);

    void createEnemyEntity(const Enemy* enemy);
    std::list<EnemyEntity>::iterator deleteEnemy(std::list<EnemyEntity>::iterator it);
};

inline const Level* BattleManager::getLevel() const
{
    return level;
}

inline const TowerEntity* BattleManager::getTowerForBuilding() const
{
    return tower_for_build;
}