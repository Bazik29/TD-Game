#pragma once

#include "Enemy.hpp"

class EnemyQueue {
public:
    struct EnemyQueueItem {
        const Enemy* enemy = nullptr;
        unsigned int number = 0;
        float spawn_delay = 0.0f;
    };

    EnemyQueue();
    EnemyQueue(unsigned int n);
    ~EnemyQueue();

    const Enemy* getNextEnemy();
    bool isEnd();
    float getSpawnDelay();

    void clear();
    inline unsigned int size();
    void resize(unsigned int n);

    EnemyQueue::EnemyQueueItem& at(unsigned int n);
    EnemyQueue::EnemyQueueItem& operator[](const unsigned int n);
    const EnemyQueue::EnemyQueueItem& operator[](const unsigned int n) const;

private:
    EnemyQueueItem* _data;
    unsigned int _size;

    unsigned int counter_enemy;
    unsigned int queue_index;
    bool at_end;
};

inline unsigned int EnemyQueue::size()
{
    return _size;
}
