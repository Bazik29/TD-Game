#include "MeshGL.hpp"

MeshGL::MeshGL()
{
    _vao = 0;
    _vbo = 0;
    _ebo = 0;
}

MeshGL::MeshGL(GLuint vao, GLuint vbo, GLuint ebo, unsigned int size)
{
    _vao = vao;
    _vbo = vbo;
    _ebo = ebo;
    _size = size;
}

MeshGL::~MeshGL()
{
}

void MeshGL::init(GLuint vao, GLuint vbo, GLuint ebo, unsigned int size)
{
    _vao = vao;
    _vbo = vbo;
    _ebo = ebo;
    _size = size;
}
