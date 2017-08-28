#pragma once
#include <glad/glad.h>
#include <memory>
#include <GameLevel.hpp>
#include <GameObject.hpp>
#include <GameBuildUnit.hpp>
#include <vector>
#include <Units.hpp>
#include <MousePositionInGame.hpp>
#include <DeselectUnit.hpp>

enum class GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};
class Camera;
class SpriteRenderer;
class Texture;
class InputHandler;
class GameGUI;

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
    void setMousePosition(GLfloat xpos, GLfloat ypos);
    void setKeyInput(int key);
    void unsetKeyInput(int key);
    void setMouseInput(int key, GLfloat xpos, GLfloat ypos);
    void unsetMouseInput(int key);
    std::vector<GameLevel> Levels;
    GLuint                 Level;
private:
    void load_textures();
    void prepare_shaders();
    void prepare_game_level();
    GLuint width, height;
    std::unique_ptr<SpriteRenderer> renderer;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<InputHandler> inputHandler;
    GLfloat deltaTime{0.0f};
    GLfloat lastFrame{0.0f};
    std::vector<Texture> hatMan;
    Units units;
    std::shared_ptr<GameGUI> gameGUI;
};
