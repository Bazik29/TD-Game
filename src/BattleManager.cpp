#include "BattleManager.hpp"

#include <glm/geometric.hpp>

#include <cstdlib>

#define ENEMY_HITBOX 0.05f


BattleManager::BattleManager()
{
	this->town_hp = 100;
}

BattleManager::~BattleManager()
{}

void BattleManager::init(int town_hp, std::vector<glm::vec2>& enemyRoute)
{
	this->town_hp = town_hp;
	this->enemyRoute = std::move(enemyRoute);
}

void BattleManager::createEnemy(EnemyProperty& prop, glm::vec2 coordinate)
{
	enemies.emplace_back(prop, coordinate);
}

void BattleManager::deleteEnemy(std::list<Enemy>::iterator enemyIt)
{
	enemies.erase(enemyIt);
}

void BattleManager::createTower(TowerProperty& prop, glm::vec2 coordinate)
{
	towers.emplace_back(prop, coordinate);
}

void BattleManager::deleteTower(std::list<Tower>::iterator towerIt)
{
	towers.erase(towerIt);
}

void BattleManager::createShell(std::list<Tower>::iterator origin, std::list<Enemy>::iterator destination)
{
	shells.emplace_back(&(*origin), &(*destination));
}

void BattleManager::deleteShell(std::list<Shell>::iterator shellIt)
{
	shells.erase(shellIt);
}

void BattleManager::update(float dt)
{
	updateEnemies(dt);
	towersAttack(dt);
	moveShells(dt);
}

void BattleManager::updateEnemies(float dt)
{
	for (auto it = enemies.begin(), end = enemies.end(); it != end; it++)
	{
		// checking hp
		if (it->current_hp <= 0)
		{
			if (it->shell_counter == 0)
			{
				auto for_delete = it;
				it++;
				deleteEnemy(for_delete);
				continue;
			} else
			{
				// todo invisible freeze while shell_counter > 0
				continue;
			}

		}

		// moving enemies
		if (it->route_index < enemyRoute.size())
		{
			glm::vec2 dir = enemyRoute[it->route_index] - it->coordinate;
			it->coordinate += glm::normalize(dir) * it->property->speed;

			if (glm::length(dir) < ENEMY_HITBOX)
			{
				it->route_index++;
			}
		} else
		{
			damageTown(it->property->damage);
		}
	}
}

void BattleManager::towersAttack(float dt)
{
	for (auto tower = towers.begin(), endT = towers.end(); tower != endT; tower++)
	{
		// update cooldown time
		if (!tower->attack_ready)
		{
			tower->cooldown_time -= dt;
			if (tower->cooldown_time <= 0.f)
			{
				tower->attack_ready = true;
				tower->cooldown_time = 0.f;
			}
		}

		// attack nearest
		if (tower->attack_ready)
		{
			for (auto enemy = enemies.begin(), endE = enemies.end(); enemy != endE; enemy++)
			{
				if (glm::length(tower->coordinate - enemy->coordinate) < tower->property->radius)
				{
					createShell(tower, enemy);

					enemy->shell_counter++;

					tower->attack_ready = false;
					tower->cooldown_time = tower->property->cooldown;
					break;
				}
			}
		}
	}
}

void BattleManager::moveShells(float dt)
{
	for (auto it = shells.begin(), end = shells.end(); it != end; it++)
	{
		glm::vec2 dir = it->destination->coordinate - it->coordinate;
		it->coordinate += glm::normalize(dir) * it->origin->property->shell_speed;


		if (glm::length(dir) < ENEMY_HITBOX)
		{
			int dmg = std::rand() % it->origin->property->damage_max + it->origin->property->damage_min;
			it->destination->current_hp -= dmg;


			it->destination->shell_counter--;

			auto for_delete = it;
			it++;
			deleteShell(for_delete);
			// continue;
		}
	}
}

void BattleManager::damageTown(int damage)
{
	town_hp -= damage;
	if (town_hp <= 0)
	{
		// todo gg
	}
}
