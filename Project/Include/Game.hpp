#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    Game(GLuint width, GLuint height);
    GameState state;
    GLboolean keys[1024];
    GLuint width, height;
};
