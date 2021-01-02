#pragma once

#include "../gameObjects/EnemyEntity.hpp"
#include "../gameObjects/Level.hpp"

#include <glm/vec2.hpp>
#include <list>

class BattleManager {
public:
    BattleManager();
    ~BattleManager();

    inline void run();
    inline void stop();
    inline bool isRun();

    inline const Level* getLevel() const;
    inline const TowerEntity* getProject() const;

    void setLevel(Level* level);
    void update(const float& dt, const glm::vec2 cursor);

    void buildTower(const Tower* tower, glm::vec2 coord);

    void setProjectTower(const Tower* tower);

private:
    Level* level;
    bool is_run;

    float ENEMY_WAY_BOX = 0.01f;

    TowerEntity* tower_project = nullptr;

    glm::vec2 cursor;
    glm::uvec2 cursor_grid;

    // auxiliary variables
    float enemy_spawn_timer;
    glm::vec2 enemy_spawn_point;
    glm::vec2 enemy_kill_point;

    void spawnEnemyFromQueue(const float& dt);

    void updateEnemies(const float& dt);
    void towersAttack(const float& dt);

    void launchShell(const TowerEntity* tower, const EnemyEntity* enemy);

    void damageTown(unsigned int dmg);

    void createEnemyEntity(const Enemy* enemy);
    std::list<EnemyEntity>::iterator deleteEnemy(std::list<EnemyEntity>::iterator it);
};

inline void BattleManager::run()
{
    this->is_run = true;
}

inline void BattleManager::stop()
{
    this->is_run = false;
}

inline bool BattleManager::isRun()
{
    return this->is_run;
}

inline const Level* BattleManager::getLevel() const
{
    return level;
}

inline const TowerEntity* BattleManager::getProject() const
{
    return tower_project;
}