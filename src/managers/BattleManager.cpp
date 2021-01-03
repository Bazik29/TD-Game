#include "BattleManager.hpp"

#include <glm/geometric.hpp>
#include <iostream>
#include <utility>

BattleManager::BattleManager()
{
    this->level = nullptr;
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

    enemy_spawn_timer = 0;
    enemy_spawn_point = level->enemy_way.firstPoint();
    enemy_kill_point = level->enemy_way.lastPoint();
}

void BattleManager::update(const float& dt, const glm::vec2& cursor)
{
    this->cursor = cursor;

    if (tower_for_build) {
        this->cursor_on_field = level->battle_grid_entity.coordToBattleGrid(cursor, cursor_grid);
        glm::vec2 cw(-100, -100);
        if (cursor_on_field)
            level->battle_grid_entity.coordToWorld(cursor_grid, cw);
        tower_for_build->setCoordinate(cw);
    }

    spawnEnemyFromQueue(dt);
    updateEnemies(dt);
    towersAttack(dt);
}

void BattleManager::selectedTowerForBuild(const Tower* tower)
{
    if (!tower_for_build)
        tower_for_build = new TowerEntity(tower, cursor);
}

bool BattleManager::tryBuildSelectedTower()
{
    bool check = level->battle_grid_entity.checkForTowerWorldCoord(cursor);
    if (check) {
        level->built_towers.push_back(std::move(*tower_for_build));
        delete tower_for_build;
        tower_for_build = nullptr;

        return level->battle_grid_entity.buildTowerWorldCoord(cursor, &level->built_towers.back());
    }
    return false;
}

void BattleManager::discardTowerForBuild()
{
    delete tower_for_build;
    tower_for_build = nullptr;
}

void BattleManager::spawnEnemyFromQueue(const float& dt)
{
    if (!level->enemy_spawn_queue.isEnd()) {
        if (enemy_spawn_timer <= 0.f) {
            const Enemy* enemy = level->enemy_spawn_queue.getNextEnemy();
            createEnemyEntity(enemy);
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
        if (it->getHP() <= 0) {
            if (it->getHauntShells() == 0) {
                auto for_delete = it;
                it = deleteEnemy(for_delete);
                continue;
            } else {
                // wait while haunt_shells != 0
                continue;
            }
        }

        // move
        if (it->getWayPoint() < level->enemy_way.size()) {
            glm::vec2 dir = level->enemy_way[it->getWayPoint()] - it->getCoordinate();
            float dist = glm::length(dir);

            glm::vec2 dir_n(0.f);
            if (dir.x != 0 || dir.y != 0)
                dir_n = glm::normalize(dir);

            glm::vec2 dway = dir_n * it->getEnemy()->getProps().getSpeed() * dt;
            float way = glm::length(dway);
            if (way >= dist - ENEMY_WAY_BOX && way <= dist + ENEMY_WAY_BOX) {
                it->incWayPoint();
            }
            if (way > dist + ENEMY_WAY_BOX) {
                it->incWayPoint();
                dway = dir;
            }

            it->move(dway);

        } else {
            auto dmg = it->getEnemy()->getProps().getDamage();
            damageTown(dmg);
            it = deleteEnemy(it);
            continue;
        }
        it++;
    }
}

void BattleManager::towersAttack(const float& dt)
{
    for (auto it_t = level->built_towers.begin(); it_t != level->built_towers.end(); it_t++) {
        if (it_t->getReloadTimer() <= 0.f) {
            // launch shell
            for (auto it_e = level->spawned_enemies.begin(); it_e != level->spawned_enemies.end(); it_e++) {
                if (glm::length(it_t->getCoordinate() - it_e->getCoordinate()) <= it_t->getTower()->getPropsT().getAttackRadius()) {
                    it_e->incHauntShells();

                    it_t->Unload();
                    it_t->incNumShells();
                    launchShell(&(*it_t), &(*it_e));
                    break;
                }
            }
        } else
            it_t->difReloadTimer(-dt);
    }
}

void BattleManager::launchShell(const TowerEntity* tower, const EnemyEntity* enemy)
{
    // std::cout << "Shell launched from (" << tower->getCoordinate().x << ", " << tower->getCoordinate().y
    //   << ") to (" << enemy->getCoordinate().x << ", " << enemy->getCoordinate().y << ")\n";
}

void BattleManager::damageTown(unsigned int dmg)
{
    // std::cout << "damageTown: -" << dmg << "\n";
}

void BattleManager::createEnemyEntity(const Enemy* enemy)
{
    EnemyEntity ee(enemy, enemy_spawn_point);
    level->spawned_enemies.push_back(std::move(ee));
}

std::list<EnemyEntity>::iterator BattleManager::deleteEnemy(std::list<EnemyEntity>::iterator it)
{
    return level->spawned_enemies.erase(it);
}
