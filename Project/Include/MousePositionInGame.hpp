#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Camera;
class MousePositionInGame
{
public:
    MousePositionInGame(std::shared_ptr<Camera> camera);
    void setMousePosition(glm::vec2 mouseCurrentPosition);
    glm::vec2 getMousePositionInGame();
    void resetMousePositionPressed();
private:
    std::shared_ptr<Camera> camera;
    glm::vec2 mousePosition;
    glm::vec2 mousePositionInGame;

};
