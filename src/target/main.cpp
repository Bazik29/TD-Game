#include <managers/GameManager.hpp>

int main()
{
    GameManager game;
    game.init();
    game.run();
    game.destroy();
    return 0;
}
