#pragma once

#include <map>
#include <string>

#include "../gameObjects/Enemy.hpp"
#include "../gameObjects/Level.hpp"
#include "../gameObjects/MeshGL.hpp"

class ResourceManager {
public:
    void loadLevel(int id, std::string path_to_json);
    Level* getLevel(int id);

private:
    std::map<std::string, MeshGL> meshesGL;
    std::map<int, Enemy> enemies;
    std::map<int, Level> levels;

    void loadEnemy(int id, std::string path_to_json);
    Enemy* getEnemy(int id);

    MeshGL* loadMeshGL(std::string path_to_json);
    MeshGL* makeMeshGL(std::string id, std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices);
};
