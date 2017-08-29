#include <InputHandler.hpp>
#include <MoveCameraUp.hpp>
#include <MoveCameraDown.hpp>
#include <MoveCameraLeft.hpp>
#include <MoveCameraRight.hpp>
#include <DeselectUnit.hpp>
#include <GLFW/glfw3.h>

InputHandler::InputHandler(std::shared_ptr<ICommand> buttonUp,
                 std::shared_ptr<ICommand> buttonDown,
                 std::shared_ptr<ICommand> buttonLeft,
                 std::shared_ptr<ICommand> buttonRight,
                 std::shared_ptr<MousePositionInGame> mousePositionInGame )
: buttonW(buttonUp), buttonS(buttonDown), buttonA(buttonLeft), buttonD(buttonRight), mousePositionInGame(mousePositionInGame)
{

}

void InputHandler::handlePlayerInput()
{
    if (keys[GLFW_KEY_W] )
    {
        buttonW ->execute();
    }
    if (keys[GLFW_KEY_S] )
    {
        buttonS ->execute();
    }
    if (keys[GLFW_KEY_A] )
    {
        buttonA ->execute();
    }
    if (keys[GLFW_KEY_D] )
    {
        buttonD ->execute();
    }
    if(mouse[GLFW_MOUSE_BUTTON_LEFT])
    {
        mousePositionInGame->setMousePosition(currentMousePosition);
    }
    if(mouse[GLFW_MOUSE_BUTTON_RIGHT])
    {
        rightMouseClick->execute();
    }

}

void InputHandler::setKeyboardKey(int key)
{
    keys[key] = GL_TRUE;
}

void InputHandler::unsetKeyboardKey(int key)
{
    keys[key] = GL_FALSE;
}

void InputHandler::setMouseKey(int key, GLfloat xpos, GLfloat ypos)
{
    currentMousePosition = glm::vec2(xpos, ypos);
    mouse[key] = GL_TRUE;
}
void InputHandler::unsetMousedKey(int key)
{
    mouse[key] = GL_FALSE;
}

glm::vec2 InputHandler::getPositionInGame()
{
    return mousePositionInGame->getMousePositionInGame();
}

void InputHandler::resetMouseKeyPressPositionInGame()
{
     mousePositionInGame->resetMousePositionPressed();
}

void InputHandler::setDeselectUnitCommand(std::shared_ptr<ICommand> rightClick)
{
    rightMouseClick = rightClick;
}
