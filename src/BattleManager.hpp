#pragma once

#include "BattleObjects.hpp"
#include <list>

class BattleManager
{
public:
	BattleManager();
	~BattleManager();

	void init(int town_hp, std::vector<glm::vec2>& enemyRoute);

	void createEnemy(EnemyProperty* prop, glm::vec2 coordinate);
	std::list<Enemy>::iterator deleteEnemy(std::list<Enemy>::iterator enemyIt);

	void createTower(TowerProperty* prop, glm::vec2 coordinate);
	std::list<Tower>::iterator deleteTower(std::list<Tower>::iterator towerIt);

	void createShell(std::list<Tower>::iterator origin, std::list<Enemy>::iterator destination);
	std::list<Shell>::iterator deleteShell(std::list<Shell>::iterator shellIt);

	void update(float dt);

//private:
	void updateEnemies(float dt);
	void towersAttack(float dt);
	void moveShells(float dt);

	void damageTown(int damage);

	int town_hp;
	std::vector<glm::vec2> enemyRoute;

	std::list<Enemy> enemies;
	std::list<Tower> towers;
	std::list<Shell> shells;
};
