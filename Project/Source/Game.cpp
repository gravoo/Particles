#include <Game.hpp>
#include <ResourceManager.hpp>
#include <iostream>
namespace
{
const glm::vec2 PLAYER_SIZE(100, 20);
const GLfloat PLAYER_VELOCITY(500.0f);
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 12.5f;

GLboolean CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // Collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // Collision only if on both axes
    return collisionX && collisionY;
}

GLboolean detectMouseClick(GameObject &one, glm::vec2 &two) // AABB - AABB collision
{
    bool collisionX = one.Position.x + one.Size.x >= two.x && two.x >= one.Position.x;
    bool collisionY = one.Position.y + one.Size.y >= two.y && two.y >= one.Position.y;
    std::cout<<one.Position.x + one.Size.x<<" "<<two.x<<" "<<collisionX<<std::endl;
    std::cout<<one.Position.y + one.Size.y<<" "<<two.y<<" "<<collisionY<<std::endl;
    // Collision only if on both axes
    return collisionX && collisionY;
}

}
Game::Game(GLuint width, GLuint height)
: state(GameState::GAME_ACTIVE), width(width), height(height), camera(glm::vec3(0.0f, 0.0f, 3.0f)), lastMousePosX(width/2), lastMousePosY(height/2),
cameraOffset(glm::vec2(0.0f, 0.0f))
{
}

void Game::Init()
{
    ResourceManager::LoadShader("../Shaders/sprite.vs", "../Shaders/sprite.frag", "sprite");
    // Configure shaders
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("view", camera.GetViewMatrix());
    ResourceManager::GetShader("sprite").SetMatrix4("projection", camera.getProjectionMatrix());
    // Load textures
    ResourceManager::LoadTexture("../Textures/background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("../Textures/face.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("../Textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("../Textures/block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture("../Textures/paddle.png", true, "paddle");
    ResourceManager::LoadTexture("../Textures/hat_man1.png", true, "hat_man1");
    ResourceManager::LoadTexture("../Textures/hat_man2.png", true, "hat_man2");
    // Load levels
    GameLevel one;
    one.Load("../levels/one.lvl", width, height);
    Levels.push_back(one);
    Level = 0;
    // Set render-specific controls
    renderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    glm::vec2 playerPos = glm::vec2(width / 2 - PLAYER_SIZE.x / 2, height - PLAYER_SIZE.y);
    player = std::make_unique<GameObject>(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    ball = std::make_unique<BallObject>(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
    glm::vec2 unitPos =  glm::vec2(width / 2, height / 2);
    glm::vec2 unitSize =  glm::vec2(width / 3, height / 3);
    buildUnit = std::make_unique<GameBuildUnit>(unitPos, unitSize, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("hat_man1"));
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
    buildUnit->move(cameraOffset, deltaTime);
}

void Game::SyncroinzeTimers()
{
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Game::DetectMouseClick()
{
    if(buildUnit->selected)
    {
        buildUnit->setDestinationToTravel(cameraOffset);
    }
    if (detectMouseClick(*buildUnit, mousePosition))
    {
        if(buildUnit->changeSelected())
            std::cout<<"UNIT SELECTED"<<std::endl;
    }
}
void Game::setMousePosition(GLfloat xpos, GLfloat ypos)
{
    float mouseX = xpos / (width  * 0.5f) - 1.0f;
    float mouseY = ypos / (height * 0.5f) - 1.0f;
    glm::mat4 invVP = glm::inverse(camera.getProjectionMatrix() * camera.GetViewMatrix());
    glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
    glm::vec4 worldPos = invVP * screenPos;
    glm::vec3 dir = glm::normalize(glm::vec3(worldPos));
    std::cout<<"World mouse Position "<<worldPos.x<<" "<<worldPos.y<<std::endl;
    std::cout<<"camera is in pos"<<camera.GetCameraCord().x<<" "<<camera.GetCameraCord().y<<std::endl;
    glm::vec4 viewport = glm::vec4(0, 0, width, height);
    glm::vec3 wincoord = glm::vec3(xpos, height - ypos - 1.0f, 1.0f);
    glm::vec3 objcoord = glm::unProject(wincoord, camera.GetViewMatrix(), camera.getProjectionMatrix(), viewport);
    std::cout<<"World mouse unProject "<<objcoord.x<<" "<<objcoord.y<<std::endl;
    mousePosition=glm::vec2(objcoord.x, objcoord.y);
    cameraOffset=glm::vec2(objcoord.x, objcoord.y);
    DetectMouseClick();
}
void Game::setLastMousePosition(GLfloat x, GLfloat y)
{
    if(firstMousePos)
    {
        lastMousePosX = x;
        lastMousePosY = y;
        firstMousePos = false;
    }
    lastMousePosX = x;
    lastMousePosY = y;

}

