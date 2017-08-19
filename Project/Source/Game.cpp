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
: state(GameState::GAME_ACTIVE), width(width), height(height), camera(glm::vec3(0.0f, 0.0f, 3.0f), width, height, 0.0f)
{
}

void Game::Init()
{
    prepare_shaders();
    load_textures();
    prepare_game_level();
    renderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    buildUnit = std::make_unique<GameBuildUnit>(
        glm::vec2(0, 0), glm::vec2(60, 40), glm::vec2(1.75f, 2.5f), hatMan, GameGrid::Location{0, 0});
}

void Game::Render()
{
    if(state == GameState::GAME_ACTIVE)
    {
        ResourceManager::GetShader("sprite").Use().SetMatrix4("view", camera.GetViewMatrix());
        buildUnit->Draw(*renderer);
        Levels.back().Draw(*renderer);
    }

}

void Game::ProcessInput()
{
    if (state == GameState::GAME_ACTIVE)
    {
        if(mouseKeys[GLFW_MOUSE_BUTTON_LEFT])
        {
            std::cout<<"Left Mouse button is pressed"<<std::endl;
            processMousePress();
        }
        if(mouseKeys[GLFW_MOUSE_BUTTON_RIGHT])
        {
            std::cout<<"Right Mouse button is pressed"<<std::endl;
            buildUnit->setSelectedFlag(false);
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
    buildUnit->update(deltaTime);
}

void Game::SyncroinzeTimers()
{
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Game::DetectMouseClick()
{
    for(auto &tile : Levels.back().Bricks)
    {
        if (detectMouseClick(tile, mousePosition))
        {
            if(!tile.IsSolid)
            {
                std::cout<<"Mouse clicked on brick "<<tile.id<<std::endl;
                if(buildUnit->selected)
                {
                    buildUnit->setDestinationToTravel(tile, Levels.back());
                }
            }
        }
    }
    if (detectMouseClick(*buildUnit, mousePosition) && !buildUnit->selected)
    {
        buildUnit->setSelectedFlag(true);
        std::cout<<"buildUnit is selected"<<std::endl;
    }
}

void Game::setMousePosition(GLfloat xpos, GLfloat ypos)
{
    if(xpos != lastXpos && ypos != lastYpos)
    {
        lastXpos = xpos;
        lastYpos = ypos;
        glm::vec4 viewport = glm::vec4(0, 0, width, height);
        glm::vec3 wincoord = glm::vec3(xpos, height - ypos - 1.0f, 1.0f);
        glm::vec3 objcoord = glm::unProject(wincoord, camera.GetViewMatrix(), camera.getProjectionMatrix(), viewport);
        std::cout<<"World mouse unProject "<<objcoord.x<<" "<<objcoord.y<<std::endl;
        mousePosition=glm::vec2(objcoord.x, objcoord.y);
    }
}

void Game::processMousePress()
{
    DetectMouseClick();
}

void Game::load_textures()
{
    ResourceManager::LoadTexture("../Textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("../Textures/block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture("../Textures/Hat_man/Walk/Hat_man1.png", GL_TRUE, "hat_man1");
    ResourceManager::LoadTexture("../Textures/Hat_man/Walk/Hat_man2.png", GL_TRUE, "hat_man2");
    ResourceManager::LoadTexture("../Textures/Hat_man/Walk/Hat_man3.png", GL_TRUE, "hat_man3");
    ResourceManager::LoadTexture("../Textures/Hat_man/Walk/Hat_man4.png", GL_TRUE, "hat_man4");
    hatMan.push_back(ResourceManager::GetTexture("hat_man1"));
    hatMan.push_back(ResourceManager::GetTexture("hat_man2"));
    hatMan.push_back(ResourceManager::GetTexture("hat_man3"));
    hatMan.push_back(ResourceManager::GetTexture("hat_man4"));
}

void Game::prepare_shaders()
{
    ResourceManager::LoadShader("../Shaders/sprite.vs", "../Shaders/sprite.frag", "sprite");
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("view", camera.GetViewMatrix());
    ResourceManager::GetShader("sprite").SetMatrix4("projection", camera.getProjectionMatrix());
}

void Game::prepare_game_level()
{
    GameLevel one;
    one.Load("../levels/one.lvl", width, height);
    Levels.push_back(one);
}
