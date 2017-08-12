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

GLboolean CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
    // Get center point circle first
    glm::vec2 center(one.Position + one.Radius);
    // Calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
    glm::vec2 aabb_center(
        two.Position.x + aabb_half_extents.x,
        two.Position.y + aabb_half_extents.y
    );
    // Get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // Add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // Retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;
    return glm::length(difference) < one.Radius;
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
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("view", view);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
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
}

void Game::Render()
{
    if(state == GameState::GAME_ACTIVE)
    {
        glm::mat4 view = camera.GetViewMatrix();
        view = glm::rotate(view, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ResourceManager::GetShader("sprite").Use().SetMatrix4("view", view);
        renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(0, 0), glm::vec2(100, 200), 0.0f );
        renderer->DrawSprite(ResourceManager::GetTexture("hat_man1"), glm::vec2(30, 100), glm::vec2(100, 200), 0.0f );
        renderer->DrawSprite(ResourceManager::GetTexture("hat_man1"), cameraOffset, glm::vec2(100, 200), 0.0f );
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
    ball->Move(deltaTime, width);
    DoCollisions();
}

void Game::SyncroinzeTimers()
{
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
void Game::DoCollisions()
{
    for (GameObject &box : Levels[Level].Bricks)
    {
        if (!box.Destroyed)
        {
            if (CheckCollision(*ball, box))
            {
                if (!box.IsSolid)
                    box.Destroyed = GL_TRUE;
            }
        }
    }
}
void Game::setMousePosition(GLfloat xpos, GLfloat ypos)
{
    float xPosOffset = lastMousePosX - xpos;
    float yPosOffset = ypos - lastMousePosY;
    std::cout<<xPosOffset<<" "<<yPosOffset<<std::endl;
    cameraOffset=+glm::vec2(xpos,ypos)+camera.GetCameraCord();
}
void Game::setLastMousePosition(GLfloat x, GLfloat y)
{
    if(firstMousePos)
    {
        lastMousePosX = x;
        lastMousePosY = y;
        firstMousePos = false;
    }
    float xPosOffset = lastMousePosX - x;
    float yPosOffset = y - lastMousePosY;
    std::cout<<xPosOffset<<" "<<yPosOffset<<std::endl;
    lastMousePosX = x;
    lastMousePosY = y;

}

