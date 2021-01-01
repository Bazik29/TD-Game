#pragma once

#include "MeshGl.hpp"
#include <glm/vec2.hpp>
#include <vector>

class ElementsMeshGl : public MeshGl {
public:
    ElementsMeshGl();
    ~ElementsMeshGl();
    ElementsMeshGl(const ElementsMeshGl& other) = default;
    ElementsMeshGl(ElementsMeshGl&& other) = default;
    ElementsMeshGl& operator=(const ElementsMeshGl& other) = default;
    ElementsMeshGl& operator=(ElementsMeshGl&& other) = default;

    void create(
        PrimitiveType type,
        const std::vector<glm::vec2>& vertices_coord,
        const std::vector<GLuint>& indices,
        GLuint coord_index = 0);

    void destroy();

private:
    GLuint buff_coords;
    GLuint buff_indices;
};
