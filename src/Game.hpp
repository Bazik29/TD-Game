#pragma once

#include <Input.hpp>
#include <Renderer.hpp>
#include <WindowGLFW.hpp>
#include <managers/BattleManager.hpp>
#include <managers/ResourceManager.hpp>
#include <gameObjects/Level.hpp>
#include <Settings.hpp>


#include <utils/FileSystem.hpp>

#include <glm/vec3.hpp>
// TODO Camera class
struct Camera {
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
};


class GameException : public std::runtime_error
{
public:
    GameException(const std::string& msg)
        : std::runtime_error(msg) {};
};

class SettingsException : public GameException
{
    public:
    SettingsException(const std::string& msg)
        : GameException(msg) {};
};

class WindowException : public GameException
{
    public:
    WindowException(const std::string& msg)
        : GameException(msg) {};
};

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    fs::path settings_file = "";
    fs::path levels_file = "../../resources/levels/_levels.json";

    WindowGLFW* _window;
    Input* _input;
    Renderer* _render;
    Camera* _camera;
    ResourceManager* _resource_mng;
    BattleManager* _battle_mng;
    Settings* _settings;

    std::vector<LevelDiscription> levels; // list of levels to display
    Level _level; // running level

    glm::mat4 projection;

    float time_run;
    float last_time;
    float dt;

    glm::vec2 mouse_window;
    glm::vec2 mouse_world;
    glm::vec3 mouse_ray;


    void initializing();
    void loadSettings(fs::path path_to_file);
    void loadSettingsDefault();
    void createWindow();
    void initRender();

    void loadLevelDiscriptions(fs::path path_to_file);
    void loadLevel(unsigned int index);

    void runLevel(float dt);

    void destroy();

    void calcMouseWorld(const glm::mat4& view, const glm::mat4& projection);

    float RayPlaneIntersect(const glm::vec3& rayPos, const glm::vec3& rayDir, const glm::vec3& N, const glm::vec3& p);
};
