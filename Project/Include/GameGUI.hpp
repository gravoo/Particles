#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <Texture.hpp>

class Camera;
class SpriteRenderer;
class GameGUI
{
public:
    GameGUI(std::shared_ptr<Camera> camera);
    void draw(SpriteRenderer &renderer);
private:
    glm::vec3   color{0.0f, 0.0f, 0.0f};
    GLfloat     rotation{0.0f};
    Texture   sprite;
    std::shared_ptr<Camera> camera;

};
