#include "ElementsMeshGl.hpp"

using namespace std;

ElementsMeshGl::ElementsMeshGl()
    : MeshGl()
{
    this->buff_coords = 0;
    this->buff_indices = 0;
}

ElementsMeshGl::~ElementsMeshGl()
{
}

ElementsMeshGl::ElementsMeshGl(const ElementsMeshGl& other)
    : MeshGl()
{
    this->buff_coords = other.buff_coords;
    this->buff_indices = other.buff_indices;
}

ElementsMeshGl::ElementsMeshGl(ElementsMeshGl&& other)
    : MeshGl()
{
    this->buff_coords = other.buff_coords;
    this->buff_indices = other.buff_indices;
}

ElementsMeshGl& ElementsMeshGl::operator=(const ElementsMeshGl& other)
{
    this->buff_coords = other.buff_coords;
    this->buff_indices = other.buff_indices;

    return *this;
}

ElementsMeshGl& ElementsMeshGl::operator=(ElementsMeshGl&& other)
{
    this->buff_coords = other.buff_coords;
    this->buff_indices = other.buff_indices;

    return *this;
}

void ElementsMeshGl::create(PrimitiveType type,
    const std::vector<glm::vec2>& vertices_coord,
    const std::vector<GLuint>& indices,
    GLuint coord_index)
{
    this->_size = indices.size();
    this->_primitive = type;

    gl::GenVertexArrays(1, &_vao);
    gl::BindVertexArray(_vao);

    gl::GenBuffers(1, &buff_coords);
    gl::BindBuffer(gl::ARRAY_BUFFER, buff_coords);
    gl::BufferData(gl::ARRAY_BUFFER, vertices_coord.size() * sizeof(glm::vec2), &vertices_coord[0], gl::STATIC_DRAW);
    gl::VertexAttribPointer(coord_index, 2, gl::FLOAT, gl::FALSE_, sizeof(glm::vec2), (void*)0);

    gl::GenBuffers(1, &buff_indices);
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buff_indices);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], gl::STATIC_DRAW);

    gl::BindVertexArray(0);
}

void ElementsMeshGl::destroy()
{
    gl::DeleteBuffers(1, &buff_indices);
    gl::DeleteBuffers(1, &buff_coords);
    gl::DeleteVertexArrays(1, &_vao);
}
