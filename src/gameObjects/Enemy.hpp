#pragma once

#include <string>
#include <glm/vec4.hpp>

#include "MeshGL.hpp"

struct Enemy
{
	unsigned int hp;
	float speed;
	MeshGL* meshGL;
	glm::vec4 color;
};
