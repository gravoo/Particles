#include <Game.hpp>
#include <ResourceManager.hpp>
#include <iostream>
#include <MoveCameraUp.hpp>
#include <MoveCameraDown.hpp>
#include <MoveCameraLeft.hpp>
#include <MoveCameraRight.hpp>
#include <Camera.hpp>
#include <SpriteRenderer.hpp>
#include <GLFW/glfw3.h>
#include <InputHandler.hpp>
#include <GameGUI.hpp>
#include <MiniMap.hpp>

namespace
{

std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, std::tuple<int,int> loc) {
  int x, y;
  std::tie (x, y) = loc;
  out << '(' << x << ',' << y << ')';
  return out;
}

}
Game::Game(GLuint width, GLuint height)
:   state(GameState::GAME_ACTIVE), width(width), height(height),
    camera(std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), width, height, 0.0f)),
    inputHandler(std::make_shared<InputHandler>(std::make_shared<MoveCameraUp>(camera), std::make_shared<MoveCameraDown>(camera),
                 std::make_shared<MoveCameraLeft>(camera), std::make_shared<MoveCameraRight>(camera),
                 std::make_shared<MousePositionInGame>(camera)))
{
}

void Game::Init()
{
    prepare_shaders();
    load_textures();
    prepare_game_level();
    units = Units(inputHandler, Levels.back());
    units.prepare_build_units(hatMan);
    renderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    gameGUI = std::make_shared<GameGUI>(camera, ResourceManager::GetTexture("gameGui"),
                                        std::make_shared<MiniMap>(Levels.back().grid, camera, ResourceManager::GetTexture("block")));
}

void Game::Render()
{
    if(state == GameState::GAME_ACTIVE)
    {
        ResourceManager::GetShader("sprite").Use().SetMatrix4("view", camera->GetViewMatrix());
        gameGUI->draw(*renderer);
        units.render(*renderer);
        Levels.back().Draw(*renderer);
    }

}

void Game::ProcessInput()
{
    if (state == GameState::GAME_ACTIVE)
    {
        inputHandler->handlePlayerInput();
    }
}

void Game::UpdateState()
{
    camera->update(deltaTime);
    units.update(deltaTime);
}

void Game::SyncroinzeTimers()
{
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Game::load_textures()
{
    ResourceManager::LoadTexture("../Textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("../Textures/block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture("../Textures/Hat_man/Walk/Hat_man1.png", GL_TRUE, "hat_man1");
    ResourceManager::LoadTexture("../Textures/Hat_man/Walk/Hat_man2.png", GL_TRUE, "hat_man2");
    ResourceManager::LoadTexture("../Textures/Hat_man/Walk/Hat_man3.png", GL_TRUE, "hat_man3");
    ResourceManager::LoadTexture("../Textures/Hat_man/Walk/Hat_man4.png", GL_TRUE, "hat_man4");
    ResourceManager::LoadTexture("../Textures/GameGui.png", GL_TRUE, "gameGui");
    hatMan.push_back(ResourceManager::GetTexture("hat_man1"));
    hatMan.push_back(ResourceManager::GetTexture("hat_man2"));
    hatMan.push_back(ResourceManager::GetTexture("hat_man3"));
    hatMan.push_back(ResourceManager::GetTexture("hat_man4"));
}

void Game::prepare_shaders()
{
    ResourceManager::LoadShader("../Shaders/sprite.vs", "../Shaders/sprite.frag", "sprite");
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("view", camera->GetViewMatrix());
    ResourceManager::GetShader("sprite").SetMatrix4("projection", camera->getProjectionMatrix());
}

void Game::prepare_game_level()
{
    GameLevel one;
    one.Load("../levels/one.lvl", width, height);
    Levels.push_back(one);
}

void Game::unsetKeyInput(int key)
{
    inputHandler->unsetKeyboardKey(key);
}
void Game::setKeyInput(int key)
{
    inputHandler->setKeyboardKey(key);
}
void Game::setMouseInput(int key, GLfloat xpos, GLfloat ypos)
{
    inputHandler->setMouseKey(key, xpos, ypos);
}
void Game::unsetMouseInput(int key)
{
    inputHandler->unsetMousedKey(key);
}

