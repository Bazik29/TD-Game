#include "ResourceManager.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <fstream>


ResourceManager::ResourceManager()
{}

ResourceManager::~ResourceManager()
{}

void ResourceManager::loadTower(fs::path filename, int id)
{
	std::ifstream src(filename);
	if (!src)
	{
		throw std::runtime_error(
			"can not open the file '" + filename.string() + "'"
		);
	}

	json j;
	src >> j;

	t_properties[id].description = j["description"].get<std::string>();
	t_properties[id].price_construction = j["price_construction"].get<int>();
	t_properties[id].price_demolition = j["price_demolition"].get<int>();
	t_properties[id].radius = j["radius"].get<int>();
	t_properties[id].cooldown = j["cooldown"].get<float>();
	t_properties[id].damage_min = j["damage_min"].get<int>();
	t_properties[id].damage_max = j["damage_max"].get<int>();
	t_properties[id].shell_speed = j["shell_speed"].get<float>();
}

TowerProperty* ResourceManager::getTowerProperty(int id)
{
	return &t_properties[id];
}

void ResourceManager::unloadTower(int id)
{
	t_properties.erase(id);
}

void ResourceManager::loadEnemy(fs::path filename, int id)
{
	std::ifstream src(filename);
	if (!src)
	{
		throw std::runtime_error(
			"can not open the file '" + filename.string() + "'"
		);
	}

	json j;
	src >> j;

	e_properties[id].description = j["description"].get<std::string>();
	e_properties[id].max_hp = j["max_hp"].get<int>();
	e_properties[id].speed = j["speed"].get<float>();
	e_properties[id].reward = j["reward"].get<int>();
	e_properties[id].damage = j["damage"].get<int>();
}

EnemyProperty* ResourceManager::getEnemyProperty(int id)
{
	return &e_properties[id];;
}

void ResourceManager::nloadEnemy(int id)
{
	e_properties.erase(id);
}
