#include "BattleGridMeshGl.hpp"

#include <utility>

BattleGridMeshGl::BattleGridMeshGl()
    : MeshGl()
{
    this->buff_coords = 0;
    this->buff_colors = 0;
}
BattleGridMeshGl::~BattleGridMeshGl()
{
}

void BattleGridMeshGl::create(PrimitiveType type,
    const std::vector<glm::vec2>& vertices_coord,
    const std::vector<float>& colors,
    GLuint coord_index, GLuint color_index)
{
    this->_size = vertices_coord.size();
    this->_primitive = type;

    gl::GenVertexArrays(1, &_vao);
    gl::BindVertexArray(_vao);

    gl::GenBuffers(1, &buff_coords);
    gl::BindBuffer(gl::ARRAY_BUFFER, buff_coords);
    gl::BufferData(gl::ARRAY_BUFFER, vertices_coord.size() * sizeof(glm::vec2), &vertices_coord[0], gl::STATIC_DRAW);
    gl::VertexAttribPointer(coord_index, 2, gl::FLOAT, gl::FALSE_, sizeof(glm::vec2), (void*)0);

    gl::GenBuffers(1, &buff_colors);
    gl::BindBuffer(gl::ARRAY_BUFFER, buff_colors);
    gl::BufferData(gl::ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], gl::DYNAMIC_DRAW);
    gl::VertexAttribPointer(color_index, 4, gl::FLOAT, gl::FALSE_, 4 * sizeof(float), (void*)0);

    gl::BindVertexArray(0);
}

void BattleGridMeshGl::setColors(const std::vector<float>& colors)
{
    gl::BindVertexArray(_vao);
    gl::BindBuffer(gl::ARRAY_BUFFER, buff_colors);
    gl::BufferData(gl::ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], gl::DYNAMIC_DRAW);
    gl::BindVertexArray(0);
}

void BattleGridMeshGl::destroy()
{
    gl::DeleteBuffers(1, &buff_colors);
    gl::DeleteBuffers(1, &buff_coords);
    gl::DeleteVertexArrays(1, &_vao);
}
