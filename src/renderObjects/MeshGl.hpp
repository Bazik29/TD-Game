#pragma once

#include <gl_core_4_3.hpp>

enum class PrimitiveType : unsigned int {
    POINTS = gl::POINTS,
    TRIANGLES = gl::TRIANGLES
};

class MeshGl {
public:
    MeshGl();
    virtual ~MeshGl();
    MeshGl(const MeshGl& other) = default;
    MeshGl(MeshGl&& other) = default;
    MeshGl& operator=(const MeshGl& other) = default;
    MeshGl& operator=(MeshGl&& other) = default;

    inline GLuint getVAO() const;
    inline unsigned int getSize() const;
    inline PrimitiveType getPrimitive() const;

protected:
    GLuint _vao;
    unsigned int _size;
    PrimitiveType _primitive;
};

inline GLuint MeshGl::getVAO() const
{
    return _vao;
}

inline unsigned int MeshGl::getSize() const
{
    return _size;
}

inline PrimitiveType MeshGl::getPrimitive() const
{
    return _primitive;
}
