#pragma once
#include<Camera.hpp>
#include<memory>

class MousePositionInGame
{
public:
    MousePositionInGame(std::shared_ptr<Camera> camera);
    void setMousePosition(glm::vec2 mouseCurrentPosition);
    glm::vec2 getMousePositionInGame();
    glm::vec2 resetMousePositionPressed();
private:
    std::shared_ptr<Camera> camera;
    glm::vec2 mousePosition;
    glm::vec2 mousePositionInGame;

};
