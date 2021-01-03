#include "BattleGridEntity.hpp"

#include <exception>
#include <glm/glm.hpp>

void BattleGridEntity::makeRoad(glm::uvec2 A, glm::uvec2 B)
{
    const int deltaX = abs(B.x - A.x);
    const int deltaY = abs(B.y - A.y);
    const int signX = A.x < B.x ? 1 : -1;
    const int signY = A.y < B.y ? 1 : -1;
    int error = deltaX - deltaY;

    this->grid[B.y * this->widht + B.x].type = Cell::Type::ROAD;

    while (A.x != B.x || A.y != B.y) {
        this->grid[A.y * this->widht + A.x].type = Cell::Type::ROAD;
        int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            A.x += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            A.y += signY;
        }
    }
}

BattleGridEntity::BattleGridEntity()
    : _mesh()
{
}

BattleGridEntity::~BattleGridEntity()
{
    _mesh.destroy();
}

void BattleGridEntity::init(unsigned int w, unsigned int h, float scale,
    const std::vector<glm::uvec2>& enemy_way,
    const std::vector<glm::uvec2>& block_cells)
{
    this->widht = w;
    this->height = h;
    this->scale = scale;

    this->grid = new BattleGridEntity::Cell[widht * height];

    for (int i = 0; i < enemy_way.size() - 1; i++) {
        makeRoad(enemy_way[i], enemy_way[i + 1]);
    }
    for (auto& i : block_cells) {
        this->grid[i.y * this->widht + i.x].type = Cell::Type::BLOCK;
    }

    setDefaultColorMap();

    std::vector<glm::vec2> vertices_coord;
    for (unsigned int j = 0; j < h; j++)
        for (unsigned int i = 0; i < w; i++)
            vertices_coord.push_back(glm::vec2(i * scale, j * scale));

    std::vector<float> colors(4 * widht * height);
    for (unsigned int i = 0; i < widht * height; i++) {
        colors[i * 4] = color_map[grid[i].type].r;
        colors[i * 4 + 1] = color_map[grid[i].type].g;
        colors[i * 4 + 2] = color_map[grid[i].type].b;
        colors[i * 4 + 3] = color_map[grid[i].type].a;
    }

    _mesh.create(PrimitiveType::POINTS, vertices_coord, colors, 0, 1);
}

void BattleGridEntity::setDefaultColorMap()
{
    this->color_map[Cell::Type::EMPTY] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    this->color_map[Cell::Type::BLOCK] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    this->color_map[Cell::Type::ROAD] = glm::vec4(0.1f, 0.1f, 0.1f, 0.0f);
    this->color_map[Cell::Type::TOWER] = glm::vec4(1.0f, 1.0f, 1.0f, 0.3f);
}

const BattleGridEntity::Cell& BattleGridEntity::getCell(glm::uvec2 pos)
{
    touchCellExcept(pos);
    return this->grid[pos.y * this->widht + pos.x];
}

void BattleGridEntity::mkTower(glm::uvec2 pos, const TowerEntity* tower)
{
    touchCellExcept(pos);
    this->grid[pos.y * this->widht + pos.x].type = BattleGridEntity::Cell::Type::TOWER;
    this->grid[pos.y * this->widht + pos.x].tower_ptr = tower;
    updateColorsMesh();
}

void BattleGridEntity::rmTower(glm::uvec2 pos)
{
    touchCellExcept(pos);
    this->grid[pos.y * this->widht + pos.x].type = BattleGridEntity::Cell::Type::EMPTY;
    this->grid[pos.y * this->widht + pos.x].tower_ptr = nullptr;
    updateColorsMesh();
}

bool BattleGridEntity::coordToBattleGrid(const glm::vec2& coords, glm::uvec2& pos)
{
    glm::uvec2 c = glm::trunc(coords / scale);

    if (touchCell(c)) {
        pos = c;
        return true;
    }
    return false;
}

bool BattleGridEntity::coordToWorld(const glm::uvec2& pos, glm::vec2& coords)
{
    if (touchCell(pos)) {
        coords = glm::vec2(pos + glm::uvec2(1, 1)) * scale - 0.5f * scale;
        return true;
    }
    return false;
}

bool BattleGridEntity::checkForTowerWorldCoord(const glm::vec2& coords)
{
    glm::uvec2 pos = glm::trunc(coords / scale);
    if (touchCell(pos))
        if (grid[pos.y * widht + pos.x].type == BattleGridEntity::Cell::Type::EMPTY)
            return true;
    return false;
}

bool BattleGridEntity::buildTower(const glm::uvec2& pos, const TowerEntity* tower)
{
    if (touchCell(pos))
        if (grid[pos.y * widht + pos.x].type == BattleGridEntity::Cell::Type::EMPTY) {
            glm::vec2 coords = glm::vec2(pos + glm::uvec2(1, 1)) * scale - 0.5f * scale;
            grid[pos.y * widht + pos.x].type = BattleGridEntity::Cell::Type::TOWER;
            grid[pos.y * widht + pos.x].tower_ptr = tower;

            return true;
        }
    return false;
}

bool BattleGridEntity::buildTowerWorldCoord(const glm::vec2& coords, const TowerEntity* tower)
{
    glm::uvec2 pos = glm::trunc(coords / scale);
    if (touchCell(pos))
        if (grid[pos.y * widht + pos.x].type == BattleGridEntity::Cell::Type::EMPTY) {
            glm::vec2 coords = glm::vec2(pos + glm::uvec2(1, 1)) * scale - 0.5f * scale;
            grid[pos.y * widht + pos.x].type = BattleGridEntity::Cell::Type::TOWER;
            grid[pos.y * widht + pos.x].tower_ptr = tower;

            return true;
        }
    return false;
}

void BattleGridEntity::touchCellExcept(const glm::uvec2& pos)
{
    if (pos.x >= widht || pos.y >= height)
        throw std::out_of_range("out_of_range BattleGridEntity");
}

bool BattleGridEntity::touchCell(const glm::uvec2& pos)
{
    return !(pos.x >= widht || pos.y >= height);
}

void BattleGridEntity::updateColorsMesh()
{
    std::vector<float> colors(4 * widht * height);
    for (unsigned int i = 0; i < widht * height; i++) {
        colors[i * 4] = color_map[grid[i].type].r;
        colors[i * 4 + 1] = color_map[grid[i].type].g;
        colors[i * 4 + 2] = color_map[grid[i].type].b;
        colors[i * 4 + 3] = color_map[grid[i].type].a;
    }
    _mesh.setColors(colors);
}
