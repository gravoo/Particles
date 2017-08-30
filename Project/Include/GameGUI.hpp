#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <Texture.hpp>

class Camera;
class SpriteRenderer;
class MiniMap;
class GameObject;

class GameGUI
{
public:
    GameGUI(std::shared_ptr<MiniMap> miniMap, std::shared_ptr<GameObject> background);
    void draw(SpriteRenderer &renderer);
    void update(glm::vec2 cameraCord);
private:
    std::shared_ptr<MiniMap> miniMap;
    std::shared_ptr<GameObject> background;
};
