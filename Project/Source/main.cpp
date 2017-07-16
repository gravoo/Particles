#include <iostream>
#include <memory>
// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Utils.hpp>
#include <GameLoop.hpp>
int main()
{
    GameLoop game{};
    game.run_game();

}
