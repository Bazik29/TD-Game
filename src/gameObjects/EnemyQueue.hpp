#pragma once

#include <vector>

#include "Enemy.hpp"

struct EnemyQueueItem {
    Enemy* enemy;
    unsigned int number;
    float spawn_delay;
    EnemyQueueItem(Enemy* e, unsigned int n, float delay)
    {
        enemy = e;
        number = n;
        spawn_delay = delay;
    };
};

struct EnemyQueue {
    std::vector<EnemyQueueItem> data;
};
