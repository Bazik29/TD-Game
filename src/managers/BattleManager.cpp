#include "BattleManager.hpp"

#include <glm/geometric.hpp>
#include <iostream>

BattleManager::BattleManager()
{
    this->level = level;
    is_run = false;
    enemy_spawn_timer = 0;
    enemy_spawn_point = glm::vec2(0.f);
    enemy_kill_point = glm::vec2(0.f);
}

BattleManager::~BattleManager()
{
}

void BattleManager::setLevel(Level* level)
{
    if (!level->is_init)
        throw std::runtime_error("BattleManager: Level not init.");
    this->level = level;
    is_run = false;
    enemy_spawn_timer = 0;
    enemy_spawn_point = level->enemy_way.firstPoint();
    enemy_kill_point = level->enemy_way.lastPoint();
}

void BattleManager::update(const float& dt)
{
    if (this->is_run) {
        spawnEnemyFromQueue(dt);
        updateEnemies(dt);
        towersAttack(dt);
    }
}

void BattleManager::spawnEnemyFromQueue(const float& dt)
{
    if (!level->enemy_spawn_queue.isEnd()) {
        if (enemy_spawn_timer <= 0.f) {
            createEnemy(level->enemy_spawn_queue.getNextEnemy());
            enemy_spawn_timer = level->enemy_spawn_queue.getSpawnDelay();
        } else {
            enemy_spawn_timer -= dt;
        }
    }
}

void BattleManager::updateEnemies(const float& dt)
{
    auto it = level->spawned_enemies.begin();
    while (it != level->spawned_enemies.end()) {
        // hp
        if (it->current_hp <= 0) {
            if (it->haunt_shells == 0) {
                auto for_delete = it;
                it = deleteEnemy(for_delete);
                continue;
            } else {
                // wait while haunt_shells != 0
                continue;
            }
        }

        // move
        if (it->way_point < level->enemy_way.size()) {
            glm::vec2 dir = level->enemy_way[it->way_point] - it->coordinate;

            if (dir.x != 0 || dir.y != 0)
                it->coordinate += glm::normalize(dir) * it->enemy->speed * dt;

            if (glm::length(dir) <= ENEMY_WAY_BOX) {
                it->way_point++;
            }
        } else {
            damageTown(it->enemy->damage);
            it = deleteEnemy(it);
            continue;
        }
        it++;
    }
}

void BattleManager::towersAttack(const float& dt)
{
    for (auto it_t = level->built_towers.begin(); it_t != level->built_towers.end(); it_t++) {
        if (it_t->cooldown_timer <= 0.f) {
            // launch shell
            for (auto it_e = level->spawned_enemies.begin(); it_e != level->spawned_enemies.end(); it_e++) {
                if (glm::length(it_t->coordinate - it_e->coordinate) <= it_t->tower->radius) {
                    it_e->haunt_shells++;
                    it_t->cooldown_timer = it_t->tower->cooldown_time;
                    launchShell(&(*it_t), &(*it_e));
                }
            }
        } else
            it_t->cooldown_timer -= dt;
    }
}

void BattleManager::launchShell(const TowerEntity* tower, const EnemyEntity* enemy)
{
    std::cout << "Shell launched from (" << tower->coordinate.x << ", " << tower->coordinate.y
              << ") to (" << enemy->coordinate.x << ", " << enemy->coordinate.y << ")\n";
}

void BattleManager::damageTown(unsigned int dmg)
{
    std::cout << "damageTown: -" << dmg << "\n";
}

void BattleManager::createEnemy(const Enemy* enemy)
{
    EnemyEntity e;
    e.enemy = enemy;
    e.current_hp = enemy->hp;
    e.haunt_shells = 0;
    e.way_point = 0;
    e.coordinate = enemy_spawn_point;
    level->spawned_enemies.push_back(e);
}

std::list<EnemyEntity>::iterator BattleManager::deleteEnemy(std::list<EnemyEntity>::iterator it)
{
    return level->spawned_enemies.erase(it);
}
