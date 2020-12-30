#include "EnemyQueue.hpp"

#include <stdexcept>

EnemyQueue::EnemyQueue()
{
    _size = 0;
    _data = nullptr;
    counter_enemy = 0;
    queue_index = 0;
    at_end = true;
}

EnemyQueue::EnemyQueue(unsigned int n)
{
    _size = n;
    _data = new EnemyQueueItem[n];
    counter_enemy = 0;
    queue_index = 0;
    at_end = false;
}

EnemyQueue::~EnemyQueue()
{
    delete[] _data;
}

Enemy* EnemyQueue::getNextEnemy()
{
    Enemy* enemy = _data[queue_index].enemy;

    // если будет спаунится последний из группы
    if (counter_enemy == _data[queue_index].number - 1) {
        // если последняя группа
        if (queue_index == _size - 1) {
            at_end = true;
            counter_enemy++;
            return enemy;
        } else {
            queue_index++;
            counter_enemy = 0;
            return enemy;
        }
    }

    counter_enemy++;
    return enemy;
}

bool EnemyQueue::isEnd()
{
    return at_end;
}

float EnemyQueue::getSpawnDelay()
{
    return _data[queue_index].spawn_delay;
}

void EnemyQueue::clear()
{
    delete[] _data;
    _size = 0;
    _data = nullptr;
    counter_enemy = 0;
    queue_index = 0;
    at_end = true;
}

EnemyQueue::EnemyQueueItem& EnemyQueue::at(unsigned int n)
{
    if (n >= _size)
        throw std::out_of_range("out_of_range EnemyQueue");
    return _data[n];
}

void EnemyQueue::resize(unsigned int n)
{
    delete[] _data;
    _size = n;
    _data = new EnemyQueueItem[n];
    counter_enemy = 0;
    queue_index = 0;
    at_end = false;
}

EnemyQueue::EnemyQueueItem& EnemyQueue::operator[](const unsigned int n)
{
    return _data[n];
}

const EnemyQueue::EnemyQueueItem& EnemyQueue::operator[](const unsigned int n) const
{
    return _data[n];
}
