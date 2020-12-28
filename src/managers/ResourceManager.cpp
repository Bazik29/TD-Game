#include "ResourceManager.hpp"

#include "../utils/jsonify.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using nlohmann::json;

MeshGL* ResourceManager::makeMeshGL(std::string id, std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices)
{
    auto it = this->meshesGL.find(id);
    if (it == this->meshesGL.end()) {
        GLuint VAO, VBO, EBO;
        unsigned int size = indices.size();

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

        this->meshesGL[id].init(VAO, VBO, EBO, size);
    }

    return &this->meshesGL[id];
}

MeshGL* ResourceManager::loadMeshGL(std::string path_to_json)
{
    std::ifstream json_file(path_to_json);
    if (!json_file) {
        throw std::runtime_error(
            "Can't open the file: '" + path_to_json + "'");
    }

    json j;
    json_file >> j;

    auto vertices = j["vertices"].get<std::vector<glm::vec2>>();
    auto indices = j["indices"].get<std::vector<unsigned int>>();

    return makeMeshGL(path_to_json, vertices, indices);
}

void ResourceManager::loadEnemy(int id, std::string path_to_json)
{
    std::ifstream json_file(path_to_json);
    if (!json_file) {
        throw std::runtime_error(
            "Can't open the file: '" + path_to_json + "'");
    }

    json j;
    json_file >> j;

    enemies[id].hp = j["hp"].get<int>();
    enemies[id].speed = j["speed"].get<float>();
    enemies[id].color = j["model"]["color"].get<glm::vec4>();
    auto mesh_path = j["model"]["mesh_path"].get<std::string>();
    enemies[id].meshGL = loadMeshGL(mesh_path);
}

Enemy* ResourceManager::getEnemy(int id)
{
    return &this->enemies.at(id);
}

void ResourceManager::loadLevel(int id, std::string path_to_json)
{
    std::ifstream json_file(path_to_json);
    if (!json_file) {
        throw std::runtime_error(
            "Can't open the file: '" + path_to_json + "'");
    }

    json j;
    json_file >> j;

    auto enemies_j = j["enemies"].get<std::vector<json>>();
    for (auto& enemy : enemies_j) {
        auto en_id = enemy["id"].get<int>();
        auto en_path = enemy["path"].get<std::string>();
        loadEnemy(en_id, en_path);
    }

    auto queue = j["queue"].get<std::vector<json>>();
    for (auto& item : queue) {
        auto en_id = item["enemy_id"].get<int>();
        auto number = item["number"].get<unsigned int>();
        auto delay = item["spawn_delay"].get<float>();
        this->levels[id].queue.data.emplace_back(getEnemy(en_id), number, delay);
    }

    this->levels[id].way.fromVector(j["way"].get<std::vector<glm::vec2>>());
}

Level* ResourceManager::getLevel(int id)
{
    return &this->levels.at(id);
}
