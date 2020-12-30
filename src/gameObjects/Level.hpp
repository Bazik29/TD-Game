#pragma once

#include "BattleGrid.hpp"
#include "EnemyEntity.hpp"
#include "EnemyQueue.hpp"
#include "EnemyWay.hpp"
#include "TowerEntity.hpp"

#include <list>
#include <vector>
#include <string>

struct LevelDiscription {
    int serial_number = 0;
    std::string path = "";
};

struct Level {
    bool is_init = false;

    BattleGrid battle_grid;
    EnemyWay enemy_way;
    EnemyQueue enemy_spawn_queue;

    std::vector<TowerEntity> built_towers;
    std::list<EnemyEntity> spawned_enemies;
};
