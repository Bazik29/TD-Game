#include "Game.hpp"

#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>

#include <iostream>

#include <cmath>

using namespace glm;

Game::Game()
{
}

Game::~Game()
{
}

void Game::destroy()
{
    _window->close();
    _window->destroy();
}

void Game::run()
{
    initializing();

    loadLevelDiscriptions(levels_file);

    bool game_state = false;

    try {
        while (!_window->shouldClose()) {
            float currentTime = glfwGetTime();
            dt = currentTime - last_time;
            last_time = currentTime;
            time_run += dt;

            _input->update();
            _window->pollEvents();

            if (_input->isKeyDown(Input::Keyboard::ESCAPE)) {
                _window->close();
                break;
            }

            if (!game_state && _input->isKeyDown(Input::Keyboard::NUM_1)) {
                loadLevel(0);
                game_state = true;
            }

            if (_input->isKey(Input::Keyboard::P)) {
                dt = 0;
            }

            if (game_state) {
                runLevel(dt);
            }

            _window->display();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    delete _window;
    delete _input;
    delete _render;
    delete _camera;
    delete _resource_mng;
    delete _battle_mng;
}

void Game::initializing()
{
    loadSettingsDefault();
    // try {
    //     loadSettings(settings_file);
    // } catch (const SettingsException& e) {
    //     std::cerr << "SettingsException: " << e.what() << '\n';
    //     std::cerr << "Set default settings.\n";
    //     loadSettingsDefault();
    // }

    try {
        createWindow();
    } catch (const WindowException& e) {
        delete _settings;
        std::cerr << "WindowException: " << e.what() << '\n';
    }

    _input = new Input();
    _input->init(*_window);

    try {
        initRender();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    _camera = new Camera();
    _camera->eye = vec3(6, 5, 13);
    _camera->center = vec3(6, 5, 0);
    _camera->up = vec3(0, 1, 0);
    mat4 view = lookAt(_camera->eye, _camera->center, _camera->up);

    // float aspect = (float)_window->getWidht() / (float)_window->getHeight();
    // float FOV = 45.f;
    // projection = perspective(glm::radians(FOV), aspect, 0.1f, 100.0f);
    // projection = ortho(-6.f, 6.f, -5.f * aspect, 5.f * aspect, 0.1f, 100.0f);
    projection = ortho(-6.f, 6.f, -5.f, 5.f, 0.1f, 100.0f);

    _render->setProjectionMatrix(projection);
    _render->setViewMatrix(view);
    gl::ClearColor(0.2, 0.2, 0.2, 1);
    gl::Enable(gl::BLEND);
    gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);

    _resource_mng = new ResourceManager();
    _battle_mng = new BattleManager();
}

void Game::loadSettings(fs::path path_to_file)
{
    try {
        _settings = new Settings();

        // TODO: load from file, mb exception

    } catch (const std::exception& e) {
        delete _settings;
        throw SettingsException(e.what()); // path to file
    }
}

void Game::loadSettingsDefault()
{
    _settings = new Settings();
    _settings->window_width = 640;
    _settings->window_height = 480;
    _settings->window_title = "develop";
    _settings->window_resizeble = true;
}

void Game::createWindow()
{
    try {
        _window = new WindowGLFW();
        _window->create(_settings->window_width, _settings->window_height, _settings->window_title, _settings->window_resizeble);

    } catch (const std::exception& e) {
        delete _window;
        throw WindowException(e.what());
    }
}

void Game::initRender()
{
    try {
        _render = new Renderer();
        _render->init();
    } catch (const std::exception& e) {
        delete _render;
        throw GameException(e.what());
    }
}

void Game::loadLevelDiscriptions(fs::path path_to_file)
{
    _resource_mng->fillLevelList(path_to_file.string(), levels);
}

void Game::loadLevel(unsigned int index)
{
    _resource_mng->loadLevel(levels[index], _level);
    _battle_mng->setLevel(&_level);
}

void Game::runLevel(float dt)
{
    mat4 view = lookAt(_camera->eye, _camera->center, _camera->up);
    _render->setViewMatrix(view);

    mouse_window = _input->getMousePosition();
    calcMouseWorld(view, projection);

    if (_input->isKeyDown(Input::Keyboard::Q)) {
        _battle_mng->selectedTowerForBuild(&_resource_mng->loaded_towers[0]);
    }

    if (_input->isKeyDown(Input::Keyboard::W)) {
        _battle_mng->discardTowerForBuild();
    }
    if (_input->isKeyDown(Input::Keyboard::E)) {
        bool res = _battle_mng->tryBuildSelectedTower();
        std::cout << (res ? "The tower was built\n" : "You can't build here!\n");
    }

    _battle_mng->update(dt, mouse_world);

    gl::Clear(gl::COLOR_BUFFER_BIT);

    _render->draw(_battle_mng->getLevel());

    auto project_tower = _battle_mng->getTowerForBuilding();
    if (project_tower)
        _render->drawTowerForBuilding(project_tower);
}

void Game::calcMouseWorld(const glm::mat4& view, const glm::mat4& projection)
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

float Game::RayPlaneIntersect(const glm::vec3& rayPos, const glm::vec3& rayDir, const glm::vec3& N, const glm::vec3& p)
{
    float ratio = glm::dot(N, rayDir);
    if (std::fabs(ratio) < 0.000001f)
        return -1.0f;
    float d = glm::dot(N, p - rayPos);
    return d / ratio;
}
