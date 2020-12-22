#pragma once
#include <gl_core_4_3.hpp>

#include "GLSLProgram.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "BattleManager.hpp"

#include <cmath>

struct MeshGL
{
	GLuint VAO, VBO, EBO;
	unsigned int size;
};


class Renderer
{
public:
	Renderer();
	~Renderer();

	void draw(std::list<Enemy>& enemies);
	void draw(std::list<Tower>& towers);
	void draw(std::list<Shell>& shells);

private:
	GLSLProgram shader;

	MeshGL enemy;
	MeshGL tower;
	MeshGL shell;

	glm::vec3 colorE = glm::vec3(1.f, 0.f, 0.f);

};


