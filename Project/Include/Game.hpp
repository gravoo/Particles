#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SpriteRenderer.hpp>
#include <memory>
#include <GameLevel.hpp>
#include <GameObject.hpp>
#include <BallObject.hpp>
#include <Camera.hpp>

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
    void setLastMousePosition(GLfloat x, GLfloat y);
    GLboolean keys[1024];
    std::vector<GameLevel> Levels;
    GLuint                 Level;
private:
    GLuint width, height;
    std::unique_ptr<SpriteRenderer> renderer;
    std::unique_ptr<GameObject> player;
    std::unique_ptr<BallObject> ball;
    Camera camera;
    GLfloat deltaTime{0.0f};
    GLfloat lastFrame{0.0f};
    GLfloat x{0},y{0};
    glm::vec2 cameraOffset;
    GLfloat lastMousePosX,lastMousePosY;
    bool firstMousePos{true};
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
};
