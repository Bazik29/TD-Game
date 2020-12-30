#pragma once

#include <glm/vec2.hpp>
#include <map>
#include <vector>

#include "TowerEntity.hpp"

#include <utility>
using myPair = std::pair<float, float>; //TODO !!!

class BattleGrid {
public:
    struct Cell {
        enum class Type {
            EMPTY,
            BLOCK,
            ROAD,
            TOWER
        };

        Type type = Type::EMPTY;
        const TowerEntity* tower_ptr = nullptr;
    };

    void init(
        unsigned int w, unsigned int h,
        const std::vector<glm::vec2>& enemy_way,
        const std::vector<glm::vec2>& block_cells);

    void clear();

    bool checkBuild(const glm::vec2& pos);
    void setTower(const glm::vec2& pos, const TowerEntity* tower);

private:
    std::map<myPair, Cell> grid;

    unsigned int widht;
    unsigned int height;
};
