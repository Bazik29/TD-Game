#include "GameManager.hpp"

#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>

#include <iostream>

#include <cmath>

using namespace glm;

GameManager::GameManager()
{
    _window = new WindowGLFW();
    _input = new Input();
    _render = new Renderer();
    _camera = new Camera();
    _resource_mng = new ResourceManager();
    _battle_mng = new BattleManager();
}

GameManager::~GameManager()
{
    delete _window;
    delete _input;
    delete _render;
    delete _camera;
    delete _resource_mng;
    delete _battle_mng;
}

void GameManager::init()
{
    try {
        unsigned int width = 800;
        unsigned int height = 600;
        const char* title = "TD-game dev";
        bool resizable = false;

        _window->create(width, height, title, resizable);

        _input->init(*_window);

        _camera->eye = vec3(6, 5, 21);
        _camera->center = vec3(6, 5, 0);
        _camera->up = vec3(0, 1, 0);

        mat4 view = lookAt(_camera->eye, _camera->center, _camera->up);
        projection = perspective(glm::radians(45.f), _window->getWidht() * 1.f / _window->getHeight(), 0.1f, 100.0f);

        // float aspect = (float)_window->getWidht() / (float)_window->getHeight();
        // float n = 8;
        // projection = ortho(-n, n, -n * aspect, n * aspect, 0.1f, 100.0f);

        _render->init();
        _render->setProjectionMatrix(projection);
        _render->setViewMatrix(view);

        _resource_mng->fillLevelList("../../resources/levels/_levels.json", levels);

        _resource_mng->loadLevel(levels[0], _level);

        _battle_mng->setLevel(&_level);

        gl::ClearColor(0.2, 0.2, 0.2, 1);

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void GameManager::destroy()
{
    _window->close();
    _window->destroy();
}

void GameManager::run()
{
    try {
        while (!_window->shouldClose()) {
            float currentTime = glfwGetTime();
            dt = currentTime - last_time;
            last_time = currentTime;

            _input->update();
            _window->pollEvents();

            mat4 view = lookAt(_camera->eye, _camera->center, _camera->up);
            _render->setViewMatrix(view);

            mouse_window = _input->getMousePosition();
            calcMouseWorld(view, projection);

            if (_input->isKeyDown(Input::Keyboard::ESCAPE)) {
                _window->close();
                break;
            }

            if (_input->isKeyDown(Input::Keyboard::Q)) {
                _battle_mng->selectedTowerForBuild(&_resource_mng->loaded_towers[0]);
            }

            if (_input->isKeyDown(Input::Keyboard::W)) {
                _battle_mng->discardTowerForBuild();
            }
            if (_input->isKeyDown(Input::Keyboard::E)) {
                bool res = _battle_mng->tryBuildSelectedTower();

                if (res)
                    std::cout << "The tower was built\n";
                else
                    std::cout << "You can't build here!\n";
            }

            _battle_mng->update(dt, mouse_world);

            gl::Clear(gl::COLOR_BUFFER_BIT);

            _render->draw(_battle_mng->getLevel());
            _render->drawProject(_battle_mng->getProject());

            _window->display();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void GameManager::calcMouseWorld(const glm::mat4& view, const glm::mat4& projection)
{
    float x = (2.0 * this->mouse_window.x / _window->getWidht() - 1);
    float y = (-2.0 * this->mouse_window.y / _window->getHeight() + 1);

    mat4 inv_mvp = inverse(projection * view);

    vec4 point_nearest = inv_mvp * vec4(x, y, -1.0f, 1.0f);
    vec4 point_far = inv_mvp * vec4(x, y, 1.0f, 1.0f);

    float w = point_nearest.w;
    point_nearest /= w;

    w = point_far.w;
    point_far /= w;

    vec3 point_ray = point_nearest;
    vec3 dir = point_far - point_nearest;
    vec3 normal_plane(0.f, 0.f, 1.f);
    vec3 point_plane(1.f, 1.f, 0.f);

    float distance = RayPlaneIntersect(point_ray, dir, normal_plane, point_plane);

    vec3 intersect_point(0.0f);
    if (distance >= 0) {
        intersect_point = point_ray + dir * distance;
    }

    this->mouse_ray = dir;
    this->mouse_world = intersect_point;
}

float GameManager::RayPlaneIntersect(const glm::vec3& rayPos, const glm::vec3& rayDir, const glm::vec3& N, const glm::vec3& p)
{
    float ratio = glm::dot(N, rayDir);
    if (std::fabs(ratio) < 0.000001f)
        return -1.0f;
    float d = glm::dot(N, p - rayPos);
    return d / ratio;
}
