#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SpriteRenderer.hpp>
#include <memory>
#include <GameLevel.hpp>
#include <GameObject.hpp>
#include <BallObject.hpp>
#include <Camera.hpp>
#include <GameBuildUnit.hpp>
#include <vector>

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
    void setMousePosition(GLfloat xpos, GLfloat ypos);
    GLboolean keys[1024];
    std::vector<GameLevel> Levels;
    GLuint                 Level;
private:
    void DetectMouseClick();
    GLuint width, height;
    std::unique_ptr<SpriteRenderer> renderer;
    std::unique_ptr<GameBuildUnit> buildUnit;
    Camera camera;
    GLfloat deltaTime{0.0f};
    GLfloat lastFrame{0.0f};
    glm::vec2 mousePosition;
};
