#pragma once

#include <gl_core_4_3.hpp>

class MeshGL {
private:
    GLuint _vao, _vbo, _ebo;
    unsigned int _size;

public:
    MeshGL();
    MeshGL(GLuint vao, GLuint vbo, GLuint ebo, unsigned int size);
    ~MeshGL();

    void init(GLuint vao, GLuint vbo, GLuint ebo, unsigned int size);

    inline GLuint getVAO();
    inline unsigned int getSize();
};

inline GLuint MeshGL::getVAO()
{
    return _vao;
}

inline unsigned int MeshGL::getSize()
{
    return _size;
}
