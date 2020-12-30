#include "BattleGrid.hpp"

#include <exception>

void BattleGrid::init(unsigned int w, unsigned int h,
    const std::vector<glm::vec2>& enemy_way,
    const std::vector<glm::vec2>& block_cells)
{
    this->widht = w;
    this->height = h;

    for (auto& e : enemy_way) {
        myPair p(e.x, e.y); //TODO !!!
        this->grid[p].type = Cell::Type::ROAD;
    }
    for (auto& b : block_cells) {
        myPair p(b.x, b.y); //TODO !!!
        this->grid[p].type = Cell::Type::BLOCK;
    }
}

void BattleGrid::clear()
{
    this->grid.clear();
}

bool BattleGrid::checkBuild(const glm::vec2& pos)
{
    myPair p(pos.x, pos.y); //TODO !!!
    return this->grid[p].type == Cell::Type::EMPTY;
}

void BattleGrid::setTower(const glm::vec2& pos, const TowerEntity* tower)
{
    if (pos.x < 0 || pos.x >= this->widht || pos.y < 0 || pos.y >= this->height)
        throw std::out_of_range("BattleGrid");

    myPair p(pos.x, pos.y); //TODO !!!
    this->grid[p].type = Cell::Type::TOWER;
    this->grid[p].tower_ptr = tower;
}
