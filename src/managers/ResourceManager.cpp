#include "ResourceManager.hpp"

#include "../gl_core/gl_core_4_3.hpp"

#include "../utils/jsonify.hpp"

#include <exception>
#include <fstream>
#include <nlohmann/json.hpp>

using nlohmann::json;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::fillLevelList(std::string path_to_json, std::vector<LevelDiscription>& level_list)
{
    std::ifstream json_file(path_to_json);
    if (!json_file) {
        throw std::runtime_error(
            "Can't open the file: '" + path_to_json + "'");
    }

    json j;
    json_file >> j;

    level_list.clear();
    level_list = j["levels"].get<std::vector<LevelDiscription>>();
}

void ResourceManager::loadLevel(const LevelDiscription& level_discription, Level& level)
{
    std::ifstream json_file(level_discription.path);
    if (!json_file) {
        throw std::runtime_error(
            "Can't open the file: '" + level_discription.path + "'");
    }

    json j;
    json_file >> j;

    auto towers_list = j["towers_list"].get<std::vector<json>>();
    for (auto& tower : towers_list) {
        loadTower(tower["id"].get<int>(), tower["path"].get<std::string>());
    }

    auto enemies_list = j["enemies_list"].get<std::vector<json>>();
    for (auto& enemy : enemies_list) {
        loadEnemy(enemy["id"].get<int>(), enemy["path"].get<std::string>());
    }

    auto queue = j["enemy_spawn_queue"].get<std::vector<json>>();
    auto queue_size = queue.size();
    level.enemy_spawn_queue.resize(queue_size);

    for (size_t i = 0; i < queue_size; i++) {
        auto en_id = queue[i]["enemy_id"].get<int>();
        auto number = queue[i]["number"].get<unsigned int>();
        auto delay = queue[i]["spawn_delay"].get<float>();

        level.enemy_spawn_queue[i].enemy = getEnemy(en_id);
        level.enemy_spawn_queue[i].number = number;
        level.enemy_spawn_queue[i].spawn_delay = delay;
    }

    auto scale = j["battle_field"]["scale"].get<unsigned int>();
    auto w = j["battle_field"]["w"].get<unsigned int>();
    auto h = j["battle_field"]["h"].get<unsigned int>();
    auto enemy_way_grid = j["battle_field"]["enemy_way"].get<std::vector<glm::uvec2>>();
    auto block_cells = j["battle_field"]["block_cells"].get<std::vector<glm::uvec2>>();

    level.battle_grid_entity.init(w, h, scale, enemy_way_grid, block_cells);
    level.enemy_way.fromVectorGrid(enemy_way_grid, scale);

    level.is_init = true;
}

void ResourceManager::loadEnemy(int id, std::string path_to_json)
{
    if (this->loaded_enemies.find(id) != this->loaded_enemies.end())
        return;

    std::ifstream json_file(path_to_json);
    if (!json_file) {
        throw std::runtime_error(
            "Can't open the file: '" + path_to_json + "'");
    }

    json j;
    json_file >> j;

    auto hp = j["hp"].get<unsigned int>();
    auto speed = j["speed"].get<float>();
    auto damage = j["damage"].get<unsigned int>();
    auto color = j["color"].get<glm::vec4>();
    auto mesh_path = j["model"]["mesh_path"].get<std::string>();
    const ElementsMeshGl* mesh = loadElementsMeshGl(mesh_path);

    loaded_enemies[id] = Enemy(EnemyProperty(hp, speed, damage, color), mesh);
}

const Enemy* ResourceManager::getEnemy(int id) const
{
    try {
        return &this->loaded_enemies.at(id);
    } catch (const std::exception& e) {
        throw std::out_of_range("out_of_range ResourceManager::getEnemy");
    };
}

void ResourceManager::loadTower(int id, std::string path_to_json)
{
    if (this->loaded_towers.find(id) != this->loaded_towers.end())
        return;

    std::ifstream json_file(path_to_json);
    if (!json_file) {
        throw std::runtime_error(
            "Can't open the file: '" + path_to_json + "'");
    }

    json j;
    json_file >> j;

    auto attack_radius = j["attack_radius"].get<float>();
    auto damage = j["damage"].get<unsigned int>();
    auto reload_time = j["reload_time"].get<float>();
    auto color_t = j["color"].get<glm::vec4>();
    auto speed = j["shell"]["speed"].get<float>();
    auto color_s = j["shell"]["color"].get<glm::vec4>();

    auto mesh_tower = j["model"]["mesh_path"].get<std::string>();
    auto mesh_shell = j["shell"]["model"]["mesh_path"].get<std::string>();

    const ElementsMeshGl* mesh_t = loadElementsMeshGl(mesh_tower);
    const ElementsMeshGl* mesh_s = loadElementsMeshGl(mesh_shell);

    this->loaded_towers[id] = Tower(TowerProperty(attack_radius, damage, reload_time, color_t), mesh_t, ShellProperty(speed, color_s), mesh_s);
}

Tower* ResourceManager::getTower(int id)
{
    try {
        return &this->loaded_towers.at(id);
    } catch (const std::exception& e) {
        throw std::out_of_range("out_of_range ResourceManager::getTower");
    };
}

const ElementsMeshGl* ResourceManager::loadElementsMeshGl(std::string path_to_json)
{
    auto it = this->loaded_meshesGl.find(path_to_json);
    if (it != this->loaded_meshesGl.end())
        return &it->second;

    std::ifstream json_file(path_to_json);
    if (!json_file) {
        throw std::runtime_error(
            "Can't open the file: '" + path_to_json + "'");
    }

    json j;
    json_file >> j;

    auto vertices = j["vertices"].get<std::vector<glm::vec2>>();
    auto indices = j["indices"].get<std::vector<unsigned int>>();

    this->loaded_meshesGl[path_to_json].create(PrimitiveType::TRIANGLES, vertices, indices);
    return &this->loaded_meshesGl[path_to_json];
}
