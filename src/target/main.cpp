#include "WindowGLFW.hpp"

#include "../Input.hpp"

#include "../managers/BattleManager.hpp"
#include "../managers/ResourceManager.hpp"
#include "Renderer.hpp"

#include <iostream>

#include "../gameObjects/Level.hpp"

struct Settings {
    const char* win_title = "TD-game";
    unsigned int win_w = 640;
    unsigned int win_h = 480;
    bool win_resizable = true;

    float fov = 45.f;
} settings;

int main()
{
    WindowGLFW window;
    Input input;
    try {

        window.create(settings.win_w, settings.win_h, settings.win_title, settings.win_resizable);

        input.init(window);

        Renderer render;
        ResourceManager resource_manager;
        BattleManager battle_manager;

        std::vector<LevelDiscription> levels;
        Level level;

        resource_manager.fillLevelList("../../resources/levels/_levels.json", levels);
        resource_manager.loadLevel(levels[0], level);

        battle_manager.setLevel(&level);
        battle_manager.run();

        double lastTime = glfwGetTime();
        float dt;

        gl::PolygonMode(gl::FRONT_AND_BACK, gl::FILL);

        gl::ClearColor(0.2, 0.2, 0.2, 1);
        while (!window.shouldClose()) {
            float currentTime = glfwGetTime();
            dt = currentTime - lastTime;
            lastTime = currentTime;

            input.update();
            window.pollEvents();

            if (input.isKeyDown(Input::Keyboard::ESCAPE)) {
                window.close();
                continue;
            }

            gl::Clear(gl::COLOR_BUFFER_BIT);

            battle_manager.update(dt);

            render.draw(level);

            window.display();
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    window.close();
    window.destroy();
    return 0;
}
