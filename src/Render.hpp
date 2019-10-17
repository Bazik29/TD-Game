#pragma once

#include "GLSLProgram.hpp"

#include "ModelGL.hpp"
#include <glm/glm.hpp>

class Render
{
public:
	Render();
	~Render();

	void setShader(GLSLProgram& shader);

	void setView(glm::mat4 view);
	void setProjection(glm::mat4 projection);
	
	void setClearColor(glm::vec4 color = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
	void clear();

	void draw(Entity& model);
private:
	GLSLProgram* shader;
	glm::mat4 projection;
	glm::mat4 view;

};
