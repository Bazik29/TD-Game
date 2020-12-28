#include <WindowGLFW.hpp>

#include "../Input.hpp"

#include "../managers/BattleManager.hpp"
#include "../managers/ResourceManager.hpp"
#include "Renderer.hpp"

int main(int argc, char const* argv[])
{

    struct Settings {
        char* win_title = "TD-game";
        unsigned int win_w = 640;
        unsigned int win_h = 480;
        bool win_resizable = true;

        float fov = 45.f;
    } settings;

    WindowGLFW window;
    window.create(settings.win_w, settings.win_h, settings.win_title, settings.win_resizable);

    Input input;
    input.init(window);

    Renderer render;
    ResourceManager resource_manager;
    BattleManager battle_manager;

    resource_manager.loadLevel(1, "../../resources/levels/way.json");

    battle_manager.setLevel(resource_manager.getLevel(1));

    double lastTime = glfwGetTime();
    float dt;


	gl::ClearColor(0, 0, 0, 1);
    while (!window.shouldClose()) {
        float currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;

        input.update();
        window.pollEvents();

        if (input.isKeyDown(Input::Keyboard::ESCAPE)) {
            window.close();
        }
 
        gl::Clear(gl::COLOR_BUFFER_BIT);

        battle_manager.update(dt);

        render.draw(battle_manager.getEnemies());

        window.display();
    }

    window.close();
    window.destroy();

    return 0;
}
