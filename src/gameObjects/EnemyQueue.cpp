#include "EnemyQueue.hpp"

#include <stdexcept>

EnemyQueue::EnemyQueue()
{
    _size = 0;
    _data = nullptr;
    counter_enemy = 0;
    counter_item = 0;
    is_end = true;
}

EnemyQueue::EnemyQueue(unsigned int n)
{
    _size = n;
    _data = new EnemyQueueItem[n];
    counter_enemy = 0;
    counter_item = 0;
    is_end = false;
}

EnemyQueue::~EnemyQueue()
{
    delete[] _data;
}

Enemy* EnemyQueue::getNextEnemy()
{
    Enemy* enemy = _data[counter_item].enemy;

    if (counter_enemy == _data[counter_item].number - 1)
        if (counter_item == _size - 1)
            is_end = true;
        else
            counter_item++;

    counter_enemy++;
    return enemy;
}

bool EnemyQueue::isEnd()
{
    return is_end;
}

float EnemyQueue::getSpawnDelay()
{
    return _data[counter_item].spawn_delay;
}

EnemyQueue::EnemyQueueItem& EnemyQueue::at(unsigned int n)
{
    if (n >= _size)
        throw std::out_of_range("EnemyQueue");
    return _data[n];
}

void EnemyQueue::resize(unsigned int n)
{
    delete[] _data;
    _size = n;
    _data = new EnemyQueueItem[n];
    counter_enemy = 0;
    counter_item = 0;
    is_end = false;
}

EnemyQueue::EnemyQueueItem& EnemyQueue::operator[](const unsigned int n)
{
    return _data[n];
}

const EnemyQueue::EnemyQueueItem& EnemyQueue::operator[](const unsigned int n) const
{
    return _data[n];
}
