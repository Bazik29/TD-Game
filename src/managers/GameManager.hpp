#pragma once

#include <Input.hpp>
#include <Renderer.hpp>
#include <WindowGLFW.hpp>
#include <managers/BattleManager.hpp>
#include <managers/ResourceManager.hpp>

#include <glm/vec3.hpp>
// TODO Camera class
struct Camera {
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
};

class GameManager {
public:
    GameManager();
    ~GameManager();

    void init();
    void destroy();

    void run();

private:
    WindowGLFW* _window;
    Input* _input;
    Renderer* _render;
    Camera* _camera;
    ResourceManager* _resource_mng;
    BattleManager* _battle_mng;

    std::vector<LevelDiscription> levels;
    Level _level;

    glm::mat4 projection;

    float time_run;
    float last_time;
    float dt;

    glm::vec2 mouse_window;
    glm::vec2 mouse_world;
    glm::vec3 mouse_ray;

    void calcMouseWorld(const glm::mat4& view, const glm::mat4& projection);

    float RayPlaneIntersect(const glm::vec3& rayPos, const glm::vec3& rayDir, const glm::vec3& N, const glm::vec3& p);
};
