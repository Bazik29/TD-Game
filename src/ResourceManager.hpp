#pragma once

#include <FileSystem.hpp>
#include <map>

#include "BattleObjects.hpp"


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void loadTower(fs::path filename, int id);
	TowerProperty* getTowerProperty(int id);
	void unloadTower(int id);

	void loadEnemy(fs::path filename, int id);
	EnemyProperty* getEnemyProperty(int id);
	void nloadEnemy(int id);
private:

	std::map<int, TowerProperty> t_properties;
	std::map<int, EnemyProperty> e_properties;
};

