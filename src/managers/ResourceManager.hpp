#pragma once

#include "../gameObjects/Enemy.hpp"
#include "../gameObjects/Level.hpp"
#include "../gameObjects/MeshGL.hpp"
#include "../gameObjects/Tower.hpp"

#include <map>
#include <string>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    void fillLevelList(std::string path_to_json, std::vector<LevelDiscription>& level_list);
    void loadLevel(const LevelDiscription& level_discription, Level& level);

private:
    std::map<int, Enemy> loaded_enemies;
    std::map<int, Tower> loaded_towers;
    std::map<std::string, MeshGL> loaded_meshesGL;

    void loadEnemy(int id, std::string path_to_json);
    Enemy* getEnemy(int id);

    void loadTower(int id, std::string path_to_json);
    Tower* getTower(int id);

    MeshGL* loadMeshGL(std::string path_to_json);
    void makeMeshGL(GLuint& VAO, GLuint& VBO, GLuint& EBO, std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices);
};
