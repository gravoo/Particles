#include <MousePositionInGame.hpp>

MousePositionInGame::MousePositionInGame(std::shared_ptr<Camera> camera)
: camera(camera), mousePositionInGame(glm::vec2(-100.0f, -100.0f))
{
}

void MousePositionInGame::setMousePosition(glm::vec2 mouseCurrentPosition)
{
    if(mouseCurrentPosition != mousePosition)
    {
        mousePosition = mouseCurrentPosition;
        glm::vec3 wincoord = glm::vec3(mousePosition.x, camera->getViewHeight() - mousePosition.y - 1.0f, 1.0f);
        glm::vec3 objcoord = glm::unProject(wincoord, camera->GetViewMatrix(), camera->getProjectionMatrix(), camera->getViewport());
        mousePositionInGame=glm::vec2(objcoord.x, objcoord.y);
    }
}

glm::vec2 MousePositionInGame::getMousePositionInGame()
{
    return mousePositionInGame;
}

void MousePositionInGame::resetMousePositionPressed()
{
    mousePositionInGame = glm::vec2(-100.0f, -100.0f);
}

