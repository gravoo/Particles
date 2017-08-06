#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SpriteRenderer.hpp>
#include <memory>
#include <GameLevel.hpp>
#include <GameObject.hpp>
#include <BallObject.hpp>
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
    void DoCollisions();
    GLboolean keys[1024];
    std::vector<GameLevel> Levels;
    GLuint                 Level;
private:
    GLuint width, height;
    std::unique_ptr<SpriteRenderer> renderer;
    std::unique_ptr<GameObject> player;
    std::unique_ptr<BallObject> ball;
    GLfloat deltaTime{0.0f};
    GLfloat lastFrame{0.0f};
};
