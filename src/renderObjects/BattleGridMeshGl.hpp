#pragma once

#include "MeshGl.hpp"

#include <glm/vec2.hpp>
#include <vector>

class BattleGridMeshGl : public MeshGl {
public:
    BattleGridMeshGl();
    ~BattleGridMeshGl();
    BattleGridMeshGl(const BattleGridMeshGl& other) = default;
    BattleGridMeshGl(BattleGridMeshGl&& other) = default;
    BattleGridMeshGl& operator=(const BattleGridMeshGl& other) = default;
    BattleGridMeshGl& operator=(BattleGridMeshGl&& other) = default;

    void create(
        PrimitiveType type,
        const std::vector<glm::vec2>& vertices_coord,
        const std::vector<float>& colors,
        GLuint coord_index=0, GLuint color_index=1);

    void setColors(const std::vector<float>& colors);

    void destroy();

private:
    GLuint buff_coords;
    GLuint buff_colors;
};
