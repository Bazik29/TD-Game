#include "BattleObjects.hpp"


Enemy::Enemy(EnemyProperty& prop, glm::vec2 coordinate)
{
	this->property = &prop;
	this->current_hp = prop.max_hp;
	this->coordinate = coordinate;
	this->route_index = 0;
	this->shell_counter = 0;
}

Enemy::~Enemy() {}


Tower::Tower(TowerProperty& prop, glm::vec2 coordinate)
{
	this->property = &prop;
	this->coordinate = coordinate;
	this->cooldown_time = prop.cooldown;
	this->attack_ready = false;
}

Tower::~Tower() {};


Shell::Shell(Tower* origin, Enemy* destination) :
	origin(origin), destination(destination)
{
	this->coordinate = origin->coordinate;
}

Shell::~Shell() {}
