#include <Game.hpp>
#include <ResourceManager.hpp>

Game::Game(GLuint width, GLuint height)
: state(GameState::GAME_ACTIVE), width(width), height(height)
{
}

void Game::Init()
{
    ResourceManager::LoadShader("../Shaders/sprite.vs", "../Shaders/sprite.frag", "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    renderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    ResourceManager::LoadTexture("../Textures/face.png", GL_TRUE, "face");
}

void Game::Render()
{
    renderer->DrawSprite(ResourceManager::GetTexture("face"),
        glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
