#include "BattleManager.hpp"/


int main(int argc, char const* argv[])
{
	BattleManager bMng;


	bMng.createEnemy(EnemyProperty(), { 1, 1 });
	bMng.createTower(TowerProperty(), { 2, 2 });


	return 0;
}
