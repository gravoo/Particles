#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SpriteRenderer.hpp>
#include <memory>

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
    void Init();
    void Render();
    GLboolean keys[1024];
    GLuint width, height;
private:
    std::unique_ptr<SpriteRenderer> renderer;
};
