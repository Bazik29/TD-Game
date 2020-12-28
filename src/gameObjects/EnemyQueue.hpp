#pragma once

#include "Enemy.hpp"

class EnemyQueue {
public:
    struct EnemyQueueItem {
        Enemy* enemy = nullptr;
        unsigned int number = 0;
        float spawn_delay = 0.f;
    };

    EnemyQueue();
    EnemyQueue(unsigned int n);
    ~EnemyQueue();

    Enemy* getNextEnemy();
    bool isEnd();
    float getSpawnDelay();

    inline unsigned int size();
    void resize(unsigned int n);

    EnemyQueue::EnemyQueueItem& at(unsigned int n);
    EnemyQueue::EnemyQueueItem& operator[](const unsigned int n);
    const EnemyQueue::EnemyQueueItem& operator[](const unsigned int n) const;

private:
    EnemyQueueItem* _data;
    unsigned int _size;

    unsigned int counter_enemy;
    unsigned int counter_item;
    bool is_end;
};

inline unsigned int EnemyQueue::size()
{
    return _size;
}
