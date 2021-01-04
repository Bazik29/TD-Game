#pragma once

#include "BattleGridEntity.hpp"
#include "EnemyEntity.hpp"
#include "EnemyQueue.hpp"
#include "EnemyWay.hpp"
#include "ShellEntity.hpp"
#include "TowerEntity.hpp"

#include <list>
#include <string>
#include <vector>

// DO NOT USE VECTOR or anything else with changing pointers to element
using LevelTowerEStorage = std::list<TowerEntity>;

struct LevelDiscription {
    int serial_number = 0;
    std::string path = "";
};

struct Level {
    bool is_init = false;

    EnemyWay enemy_way;
    EnemyQueue enemy_spawn_queue;

    BattleGridEntity battle_grid_entity;
    LevelTowerEStorage built_towers;
    std::list<EnemyEntity> spawned_enemies;
    std::list<ShellEntity> launched_shells;
};
