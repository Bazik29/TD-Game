#pragma once

#include "../gameObjects/Enemy.hpp"
#include "../gameObjects/Level.hpp"
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

    std::map<int, Tower> loaded_towers;
private:
    std::map<int, Enemy> loaded_enemies;
    std::map<std::string, ElementsMeshGl> loaded_meshesGl;

    void loadEnemy(int id, std::string path_to_json);
    const Enemy* getEnemy(int id) const;

    void loadTower(int id, std::string path_to_json);
    Tower* getTower(int id);

    const ElementsMeshGl* loadElementsMeshGl(std::string path_to_json);
};
