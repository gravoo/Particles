#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SpriteRenderer.hpp>
#include <memory>
#include <GameLevel.hpp>
#include <GameObject.hpp>
#include <Camera.hpp>
#include <GameBuildUnit.hpp>
#include <vector>
#include <InputHandler.hpp>
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
    void setKeyInput(int key);
    void unsetKeyInput(int key);
    void setMouseInput(int key, GLfloat xpos, GLfloat ypos);
    void unsetMouseInput(int key);
    GLboolean mouseKeys[8];
    std::vector<GameLevel> Levels;
    GLuint                 Level;
private:
    void load_textures();
    void prepare_shaders();
    void prepare_game_level();
    void processMousePress();
    void DetectMouseClick();
    void prepare_build_units();
    GLuint width, height;
    std::unique_ptr<SpriteRenderer> renderer;
    std::vector<std::unique_ptr<GameBuildUnit>> buildUnits;
    std::shared_ptr<Camera> camera;
    InputHandler inputHandler;
    GLfloat deltaTime{0.0f};
    GLfloat lastFrame{0.0f};
    glm::vec2 mousePosition;
    GLfloat lastXpos{0.0f}, lastYpos{0.0f};
    std::vector<Texture> hatMan;
};
