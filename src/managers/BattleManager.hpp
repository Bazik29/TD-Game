#pragma once

#include <list>

#include "../gameObjects/EnemyEntity.hpp"
#include "../gameObjects/Level.hpp"

class BattleManager {

public:
    void setLevel(Level* lvl);

    void update(float dt);

    inline const std::list<EnemyEntity>& getEnemies() const
    {
        return this->enemies;
    }

private:
    void runQueue(float dt);

    void spawnEnemy(Enemy* enemy);
    std::list<EnemyEntity>::iterator deleteEnemy(std::list<EnemyEntity>::iterator enemyIt);

    void updateEnemies(float dt);
    // void towersAttack(float dt);
    // void moveShells(float dt);

    void damageTown(int damage);

    Level* level;

    float spawn_timer;
    std::list<EnemyEntity> enemies;
};
