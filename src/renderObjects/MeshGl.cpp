#include "MeshGl.hpp"

MeshGl::MeshGl()
{
    this->_vao = 0;
    this->_size = 0;
    this->_primitive = PrimitiveType::POINTS;
}

MeshGl::~MeshGl()
{
}
