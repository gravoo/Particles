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
    void UpdateState();
    void ProcessInput();
    void SyncroinzeTimers();
    GLboolean keys[1024];
private:
    GLuint width, height;
    std::unique_ptr<SpriteRenderer> renderer;
    GLfloat deltaTime{0.0f};
    GLfloat lastFrame{0.0f};
};
