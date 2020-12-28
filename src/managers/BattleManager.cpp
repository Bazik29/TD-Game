#include "BattleManager.hpp"

#include <glm/geometric.hpp>

#include <cstdlib>

#include "ResourceManager.hpp"

#include <iostream>

#define ENEMY_HITBOX 0.1f

void BattleManager::setLevel(Level* lvl)
{
    this->level = lvl;
    queue_pos = 0;
    enemy_spawns = 0;
    spawn_timer = 0;
}

void BattleManager::runQueue(float dt)
{
    if (queue_pos >= level->queue.data.size())
        return;
    if (enemy_spawns == level->queue.data[queue_pos].number) {
        queue_pos++;
        enemy_spawns = 0;
    }

    if (spawn_timer <= 0.f) {
        spawnEnemy(level->queue.data[queue_pos].enemy);
        enemy_spawns++;
        spawn_timer = level->queue.data[queue_pos].spawn_delay;
    } else {
        spawn_timer -= dt;
    }
}

void BattleManager::spawnEnemy(Enemy* enemy)
{
    EnemyEntity e;
    e.enemy = enemy;
    e.current_hp = enemy->hp;
    e.haunt_shells = 0;
    e.way_point = 0;
    e.coordinate = level->way.points[e.way_point];
    enemies.push_back(e);
}

std::list<EnemyEntity>::iterator BattleManager::deleteEnemy(std::list<EnemyEntity>::iterator enemyIt)
{
    return enemies.erase(enemyIt);
}

// void BattleManager::spawnTower(TowerProperty* prop, glm::vec2 coordinate)
// {
//     towers.emplace_back(prop, coordinate);
// }

// std::list<Tower>::iterator BattleManager::deleteTower(std::list<Tower>::iterator towerIt)
// {
//     return towers.erase(towerIt);
// }

// void BattleManager::spawnShell(std::list<Tower>::iterator origin, std::list<Enemy>::iterator destination)
// {
//     shells.emplace_back(&(*origin), &(*destination));
// }

// std::list<Shell>::iterator BattleManager::deleteShell(std::list<Shell>::iterator shellIt)
// {
//     return shells.erase(shellIt);
// }

void BattleManager::update(float dt)
{
    runQueue(dt);
    updateEnemies(dt);
    // towersAttack(dt);
    // moveShells(dt);
}

void BattleManager::updateEnemies(float dt)
{
    auto it = enemies.begin();
    while (it != enemies.end()) {
        // checking hp
        if (it->current_hp <= 0) {
            if (it->haunt_shells == 0) {
                auto for_delete = it;
                it = deleteEnemy(for_delete);
                continue;
            } else {
                // todo invisible freeze while haunt_shells > 0, not_render = true
                continue;
            }
        }

        // moving enemies
        if (it->way_point < level->way.points.size()) {
            glm::vec2 dir = level->way.points[it->way_point] - it->coordinate;

            if (dir.x != 0 || dir.y != 0)
                it->coordinate += glm::normalize(dir) * it->enemy->speed * dt;

            if (glm::length(dir) <= ENEMY_HITBOX) {
                it->way_point++;
            }
        } else {
            damageTown(100);

            it = deleteEnemy(it);
            continue;
        }
        it++;
    }
}

// void BattleManager::towersAttack(float dt)
// {
//     for (auto tower = towers.begin(), endT = towers.end(); tower != endT; tower++) {
//         // update cooldown time
//         if (!tower->attack_ready) {
//             tower->cooldown_time -= dt;
//             if (tower->cooldown_time <= 0.f) {
//                 tower->attack_ready = true;
//                 tower->cooldown_time = 0.f;
//             }
//         }

//         // attack first nearest
//         if (tower->attack_ready) {
//             for (auto enemy = enemies.begin(), endE = enemies.end(); enemy != endE; enemy++) {
//                 if (glm::length(tower->coordinate - enemy->coordinate) < tower->property->radius) {
//                     spawnShell(tower, enemy);

//                     enemy->shell_counter++;

//                     tower->attack_ready = false;
//                     tower->cooldown_time = tower->property->cooldown;
//                     break;
//                 }
//             }
//         }
//     }
// }

// void BattleManager::moveShells(float dt)
// {
//     auto it = shells.begin();
//     while (it != shells.end()) {
//         glm::vec2 dir = it->destination->coordinate - it->coordinate;
//         if (dir.x != 0 && dir.y != 0)
//             it->coordinate += glm::normalize(dir) * it->origin->property->shell_speed * dt;

//         if (glm::length(dir) < ENEMY_HITBOX) {
//             int dmg = std::rand() % it->origin->property->damage_max + it->origin->property->damage_min;
//             it->destination->current_hp -= dmg;
//             it->destination->shell_counter--;
//             it = deleteShell(it);
//             continue;
//         }
//         it++;
//     }
// }

void BattleManager::damageTown(int damage)
{
    // town_hp -= damage;
    // if (town_hp <= 0) {
    //     // todo gg
    // }
    std::cout << "damageTown: -" << damage << " \n";
}
