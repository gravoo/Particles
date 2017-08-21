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
: state(GameState::GAME_ACTIVE), width(width), height(height), camera(std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), width, height, 0.0f)), inputHandler(std::make_shared<MoveCameraUp>(camera), std::make_shared<MoveCameraDown>(camera), std::make_shared<MoveCameraLeft>(camera), std::make_shared<MoveCameraRight>(camera))
{
}

void Game::Init()
{
    prepare_shaders();
    load_textures();
    prepare_game_level();
    prepare_build_units();
    renderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
}

void Game::Render()
{
    if(state == GameState::GAME_ACTIVE)
    {
        ResourceManager::GetShader("sprite").Use().SetMatrix4("view", camera->GetViewMatrix());
        for(auto & buildUnit : buildUnits)
        {
            buildUnit->Draw(*renderer);
        }
        Levels.back().Draw(*renderer);
    }

}

void Game::ProcessInput()
{
    if (state == GameState::GAME_ACTIVE)
    {
        inputHandler.handleKeyboardInput(deltaTime);
        if(mouseKeys[GLFW_MOUSE_BUTTON_LEFT])
        {
            std::cout<<"Left Mouse button is pressed"<<std::endl;
            processMousePress();
        }
        if(mouseKeys[GLFW_MOUSE_BUTTON_RIGHT])
        {
            std::cout<<"Right Mouse button is pressed"<<std::endl;
            for(auto & buildUnit : buildUnits)
            {
                buildUnit->setSelectedFlag(false);
            }
        }
    }
}

void Game::UpdateState()
{
    for(auto & buildUnit : buildUnits)
    {
        buildUnit->update(deltaTime);
    }
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
            if(Levels.back().grid->passable(tile.id))
            {
                for(auto & buildUnit : buildUnits)
                {
                    if(buildUnit->selected)
                    {
                        buildUnit->setDestinationToTravel(tile);
                    }
                }

            }
        }
    }
    for(auto & buildUnit : buildUnits)
    {
        if (detectMouseClick(*buildUnit, mousePosition) && !buildUnit->selected)
        {
            for(auto & buildUnit : buildUnits)
            {
                buildUnit->setSelectedFlag(false);
            }
            buildUnit->setSelectedFlag(true);
        }
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
        glm::vec3 objcoord = glm::unProject(wincoord, camera->GetViewMatrix(), camera->getProjectionMatrix(), viewport);
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
    ResourceManager::GetShader("sprite").Use().SetMatrix4("view", camera->GetViewMatrix());
    ResourceManager::GetShader("sprite").SetMatrix4("projection", camera->getProjectionMatrix());
}

void Game::prepare_game_level()
{
    GameLevel one;
    one.Load("../levels/one.lvl", width, height);
    Levels.push_back(one);
}

void Game::prepare_build_units()
{
    buildUnits.push_back(std::make_unique<GameBuildUnit>(
        glm::vec2(0, 0), glm::vec2(60, 40), glm::vec2(1.75f, 2.5f), hatMan, GameGrid::Location{0, 0}, Levels.back().grid));
    buildUnits.push_back(std::make_unique<GameBuildUnit>(
        glm::vec2(0, 70), glm::vec2(60, 40), glm::vec2(1.75f, 2.5f), hatMan, GameGrid::Location{0, 1}, Levels.back().grid));
    buildUnits.push_back(std::make_unique<GameBuildUnit>(
        glm::vec2(0, 140), glm::vec2(60, 40), glm::vec2(1.75f, 2.5f), hatMan, GameGrid::Location{0, 2}, Levels.back().grid));
}
void Game::unsetKeyInput(int key)
{
    inputHandler.unsetKeyboardKey(key);
}
void Game::setKeyInput(int key)
{
    inputHandler.setKeyboardKey(key);
}

