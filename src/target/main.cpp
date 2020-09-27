#include "ResourceManager.hpp"
#include "BattleManager.hpp"


#include <iostream>

int main(int argc, char const* argv[])
{
	ResourceManager resMng;

	resMng.loadTower("../../resources/tower.json", 0);
	resMng.loadEnemy("../../resources/enemy.json", 0);

	BattleManager bMng;


	bMng.createEnemy(resMng.getEnemyProperty(0), { 1, 1 });
	bMng.createTower(resMng.getTowerProperty(0), { 2, 2 });


	return 0;
}
