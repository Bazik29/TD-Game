#pragma once

#include "EnemyEntity.hpp"
#include "EnemyQueue.hpp"
#include "EnemyWay.hpp"
#include "TowerEntity.hpp"
#include "BattleGridEntity.hpp"
#include "ShellEntity.hpp"

#include <list>
#include <vector>
#include <string>

struct LevelDiscription {
    int serial_number = 0;
    std::string path = "";
};

struct Level {
    bool is_init = false;

    EnemyWay enemy_way;
    EnemyQueue enemy_spawn_queue;

    BattleGridEntity battle_grid_entity;
    std::vector<TowerEntity> built_towers;
    std::list<EnemyEntity> spawned_enemies;
    std::list<ShellEntity> shells;
};
