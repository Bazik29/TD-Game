#pragma once

#include "../renderObjects/BattleGridMeshGl.hpp"

#include "TowerEntity.hpp"
#include <glm/vec2.hpp>
#include <map>

class BattleGridEntity {
public:
    struct Cell {
        enum class Type : unsigned {
            EMPTY,
            BLOCK,
            ROAD,
            TOWER
        };

        Type type = Type::EMPTY;
        const TowerEntity* tower_ptr = nullptr;
    };

    BattleGridEntity();
    ~BattleGridEntity();

    void init(
        unsigned int w, unsigned int h, float scale,
        const std::vector<glm::uvec2>& enemy_way,
        const std::vector<glm::uvec2>& block_cells);

    void setDefaultColorMap();
    const BattleGridEntity::Cell& getCell(glm::uvec2 pos);
    void mkTower(glm::uvec2 pos, const TowerEntity* tower);
    void rmTower(glm::uvec2 pos);

    inline const BattleGridMeshGl& mesh() const;

    bool coordToBattleGrid(const glm::vec2& coords, glm::uvec2& pos);
    bool coordToWorld(const glm::uvec2& pos, glm::vec2& coords);
    bool coordOnBattleGrid(const glm::vec2& coords, glm::uvec2& bg_pos, glm::vec2& coords_for_tower);
    bool checkForTowerWorldCoord(const glm::vec2& coords);
    bool buildTower(const glm::uvec2& pos, const TowerEntity* tower);
    bool buildTowerWorldCoord(const glm::vec2& coords, const TowerEntity* tower);

private:
    BattleGridMeshGl _mesh;

    std::map<BattleGridEntity::Cell::Type, glm::vec4> color_map;
    unsigned int widht;
    unsigned int height;
    float scale;
    BattleGridEntity::Cell* grid;

    void makeRoad(glm::uvec2 A, glm::uvec2 B);
    void touchCellExcept(const glm::uvec2& pos);
    bool touchCell(const glm::uvec2& pos);
    void updateColorsMesh();
};

inline const BattleGridMeshGl& BattleGridEntity::mesh() const
{
    return this->_mesh;
}
