#pragma once

#include "../gameObjects/Enemy.hpp"
#include "../gameObjects/Level.hpp"
#include "../gameObjects/MeshGL.hpp"
#include "../gameObjects/Tower.hpp"

#include "../renderObjects/ElementsMeshGl.hpp"

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

    std::map<std::string, ElementsMeshGl> loaded_meshesGl;

    void loadEnemy(int id, std::string path_to_json);
    const Enemy* getEnemy(int id) const;

    void loadTower(int id, std::string path_to_json);
    Tower* getTower(int id);

    const ElementsMeshGl* loadMeshGl(std::string path_to_json);

    MeshGL* loadMeshGL(std::string path_to_json);
    void makeMeshGL(GLuint& VAO, GLuint& VBO, GLuint& EBO, std::vector<glm::vec2>& vertices, std::vector<unsigned int>& indices);
};
