#pragma once

#include <string>
#include <vector>
#include <utility>
#include <glm/vec2.hpp>

struct EnemyProperty
{
	std::string description;
	int max_hp;
	float speed;
	int reward;
	int damage;

	//enemy_model
};

class Enemy
{
public:
	Enemy() = delete;
	Enemy(EnemyProperty* prop, glm::vec2 coordinate);
	~Enemy();


	EnemyProperty* property;
	int current_hp;
	glm::vec2 coordinate;
	int route_index;
	int shell_counter;
};


struct TowerProperty
{
	std::string description;
	int price_construction;
	int price_demolition;
	int radius;
	float cooldown;
	int damage_min;
	int damage_max;
	// attack_type

	float shell_speed;
	// shell_type
	// shell_model

	// tower_model
	// shell_model
};

class Tower
{
public:
	Tower() = delete;
	Tower(TowerProperty* prop, glm::vec2 coordinate);
	~Tower();

	TowerProperty* property;
	glm::vec2 coordinate;
	bool attack_ready;
	float cooldown_time;
};



class Shell
{
public:
	Shell() = delete;
	Shell(Tower* origin, Enemy* destination);
	~Shell();

	Tower* origin;
	Enemy* destination;
	glm::vec2 coordinate;
};

Enemy::Enemy(EnemyProperty* prop, glm::vec2 coordinate)
{
	this->property = prop;
	this->current_hp = prop->max_hp;
	this->coordinate = coordinate;
	this->route_index = 0;
	this->shell_counter = 0;
}

Enemy::~Enemy() {}


Tower::Tower(TowerProperty* prop, glm::vec2 coordinate)
{
	this->property = prop;
	this->coordinate = coordinate;
	this->cooldown_time = prop->cooldown;
	this->attack_ready = false;
}

Tower::~Tower() {};


Shell::Shell(Tower* origin, Enemy* destination) :
	origin(origin), destination(destination)
{
	this->coordinate = origin->coordinate;
}

Shell::~Shell() {}