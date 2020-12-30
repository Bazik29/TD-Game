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

    auto w = j["battle_field"]["w"].get<unsigned int>();
    auto h = j["battle_field"]["h"].get<unsigned int>();
    auto enemy_way_grid = j["battle_field"]["enemy_way"].get<std::vector<glm::vec2>>();
    auto block_cells = j["battle_field"]["block_cells"].get<std::vector<glm::vec2>>();

    level.battle_grid.init(w, h, enemy_way_grid, block_cells);
    level.enemy_way.fromVectorGrid(enemy_way_grid, 2.f);
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

    loaded_enemies[id].hp = j["hp"].get<int>();
    loaded_enemies[id].speed = j["speed"].get<float>();
    loaded_enemies[id].damage = j["damage"].get<float>();
    loaded_enemies[id].color = j["model"]["color"].get<glm::vec4>();
    auto mesh_path = j["model"]["mesh_path"].get<std::string>();
    loaded_enemies[id].meshGL = loadMeshGL(mesh_path);
}

Enemy* ResourceManager::getEnemy(int id)
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

    this->loaded_towers[id].radius = j["radius"].get<float>();
    this->loaded_towers[id].damage = j["damage"].get<unsigned int>();
    this->loaded_towers[id].cooldown_time = j["cooldown_time"].get<float>();

    this->loaded_towers[id].color = j["model"]["color"].get<glm::vec4>();
    auto mesh_tower = j["model"]["mesh_path"].get<std::string>();
    this->loaded_towers[id].meshGL = loadMeshGL(mesh_tower);

    this->loaded_towers[id].shell.speed = j["shell"]["speed"].get<float>();
    this->loaded_towers[id].shell.color = j["shell"]["model"]["color"].get<glm::vec4>();
    auto mesh_shell = j["shell"]["model"]["mesh_path"].get<std::string>();
    this->loaded_towers[id].shell.meshGL = loadMeshGL(mesh_shell);
}

Tower* ResourceManager::getTower(int id)
{
    try {
        return &this->loaded_towers.at(id);
    } catch (const std::exception& e) {
        throw std::out_of_range("out_of_range ResourceManager::getTower");
    };
}

MeshGL* ResourceManager::loadMeshGL(std::string path_to_json)
{
    auto it = this->loaded_meshesGL.find(path_to_json);
    if (it != this->loaded_meshesGL.end())
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

    GLuint VAO, VBO, EBO;
    makeMeshGL(VAO, VBO, EBO, vertices, indices);

    this->loaded_meshesGL[path_to_json].init(VAO, VBO, EBO, indices.size());
    return &this->loaded_meshesGL[path_to_json];
}

void ResourceManager::makeMeshGL(GLuint& VAO, GLuint& VBO, GLuint& EBO, std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices)
{
    gl::GenVertexArrays(1, &VAO);
    gl::GenBuffers(1, &VBO);
    gl::GenBuffers(1, &EBO);

    gl::BindVertexArray(VAO);

    gl::BindBuffer(gl::ARRAY_BUFFER, VBO);
    gl::BufferData(gl::ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], gl::STATIC_DRAW);

    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, EBO);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], gl::STATIC_DRAW);

    // vertex positions
    gl::EnableVertexAttribArray(0);
    gl::VertexAttribPointer(0, 2, gl::FLOAT, gl::FALSE_, sizeof(glm::vec2), (void*)0);

    gl::BindVertexArray(0);
}
