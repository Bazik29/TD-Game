#include "Render.hpp"


Render::Render()
{
	this->shader = nullptr;
}

Render::~Render()
{}

void Render::setShader(GLSLProgram& shader)
{
	this->shader = &shader;
}

void Render::setView(glm::mat4 view)
{
	this->view = view;
}

void Render::setProjection(glm::mat4 projection)
{
	this->projection = projection;
}

void Render::setClearColor(glm::vec4 color)
{
	gl::ClearColor(color.r, color.g, color.b, color.a);
}

void Render::clear()
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
}

void Render::draw(Entity& entity)
{
	shader->start();
	shader->setUniform("projection", projection);
	shader->setUniform("view", view);


	shader->setUniform("model", entity.modelMat4);
	for (const auto& meshGL : entity.modelGL->meshesGL)
	{
		GLuint id_diff = meshGL.materialGL.textures_id.at(TextureType::DIFFUSE);
		gl::ActiveTexture(gl::TEXTURE0);
		gl::BindTexture(gl::TEXTURE_2D, id_diff);

		gl::BindVertexArray(meshGL.VAO);
		gl::DrawElements(gl::TRIANGLES, meshGL.size, gl::UNSIGNED_INT, 0);
		gl::BindVertexArray(0);
	}

	shader->stop();
}
