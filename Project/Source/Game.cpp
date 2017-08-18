#include <Game.hpp>
#include <ResourceManager.hpp>
#include <iostream>
namespace
{

GLboolean detectMouseClick(GameObject &one, glm::vec2 &two) // AABB - AABB collision
{
    bool collisionX = one.Position.x + one.Size.x >= two.x && two.x >= one.Position.x;
    bool collisionY = one.Position.y + one.Size.y >= two.y && two.y >= one.Position.y;
    return collisionX && collisionY;
}

std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, std::tuple<int,int> loc) {
  int x, y;
  std::tie (x, y) = loc;
  out << '(' << x << ',' << y << ')';
  return out;
}

}
Game::Game(GLuint width, GLuint height)
: state(GameState::GAME_ACTIVE), width(width), height(height), camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
}

void Game::Init()
{
    ResourceManager::LoadShader("../Shaders/sprite.vs", "../Shaders/sprite.frag", "sprite");
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("view", camera.GetViewMatrix());
    ResourceManager::GetShader("sprite").SetMatrix4("projection", camera.getProjectionMatrix());
    ResourceManager::LoadTexture("../Textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("../Textures/block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture("../Textures/hat_man1.png", true, "hat_man1");
    ResourceManager::LoadTexture("../Textures/hat_man2.png", true, "hat_man2");
    GameLevel one;
    one.Load("../levels/one.lvl", width, height);
    Levels.push_back(one);
    Level = 0;
    renderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    buildUnit = std::make_unique<GameBuildUnit>(
        glm::vec2(0, 0), glm::vec2(60, 40), glm::vec2(100.0f, -350.0f), ResourceManager::GetTexture("hat_man1"), GameGrid::Location{0, 0});
}

void Game::Render()
{
    if(state == GameState::GAME_ACTIVE)
    {
        glm::mat4 view = camera.GetViewMatrix();
        view = glm::rotate(view, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ResourceManager::GetShader("sprite").Use().SetMatrix4("view", view);
        buildUnit->Draw(*renderer);
        Levels[Level].Draw(*renderer);
    }

}

void Game::ProcessInput()
{
    if (state == GameState::GAME_ACTIVE)
    {
        if(keys[GLFW_MOUSE_BUTTON_LEFT])
        {
        }
        if (keys[GLFW_KEY_W] )
        {
            camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
        }
        if (keys[GLFW_KEY_S])
        {
            camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
        }
        if (keys[GLFW_KEY_A])
        {
            camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
        }
        if (keys [GLFW_KEY_D])
        {
            camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
        }

    }
}

void Game::UpdateState()
{
    buildUnit->move();
}

void Game::SyncroinzeTimers()
{
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Game::DetectMouseClick()
{
    for(auto &x : Levels.back().Bricks)
    {
        if (detectMouseClick(x, mousePosition))
        {
            if(!x.IsSolid)
            {
                std::cout<<"Mouse clicked on brick "<<x.id<<std::endl;
                if(buildUnit->selected)
                {
                    buildUnit->setDestinationToTravel(x, Levels.back());
                }
            }
        }
    }
    if (detectMouseClick(*buildUnit, mousePosition))
    {
        buildUnit->changeSelected();
        std::cout<<"Mouse clicked on buildUnit "<<std::endl;
    }
}
void Game::setMousePosition(GLfloat xpos, GLfloat ypos)
{
    glm::vec4 viewport = glm::vec4(0, 0, width, height);
    glm::vec3 wincoord = glm::vec3(xpos, height - ypos - 1.0f, 1.0f);
    glm::vec3 objcoord = glm::unProject(wincoord, camera.GetViewMatrix(), camera.getProjectionMatrix(), viewport);
    std::cout<<"World mouse unProject "<<objcoord.x<<" "<<objcoord.y<<std::endl;
    mousePosition=glm::vec2(objcoord.x, objcoord.y);
    DetectMouseClick();
}


