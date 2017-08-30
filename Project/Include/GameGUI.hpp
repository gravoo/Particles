#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <Texture.hpp>

class Camera;
class SpriteRenderer;
class MiniMap;

class GameGUI
{
public:
    GameGUI(std::shared_ptr<Camera> camera, Texture sprite, std::shared_ptr<MiniMap> miniMap);
    void draw(SpriteRenderer &renderer);
private:
    glm::vec3   color{1.0f};
    GLfloat     rotation{0.0f};
    Texture   sprite;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<MiniMap> miniMap;
};
