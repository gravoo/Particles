#include <InputHandler.hpp>
#include <cassert>
InputHandler::InputHandler(std::shared_ptr<ICommand> buttonUp,
                 std::shared_ptr<ICommand> buttonDown,
                 std::shared_ptr<ICommand> buttonLeft,
                 std::shared_ptr<ICommand> buttonRight)
: buttonW(buttonUp), buttonS(buttonDown), buttonA(buttonLeft), buttonD(buttonRight)
{

}

void InputHandler::handleKeyboardInput(GLfloat deltaTime)
{
    if (keys[GLFW_KEY_W] )
    {
        buttonW ->execute(deltaTime);
    }
    if (keys[GLFW_KEY_S] )
    {
        buttonS ->execute(deltaTime);
    }
    if (keys[GLFW_KEY_A] )
    {
        buttonA ->execute(deltaTime);
    }
    if (keys[GLFW_KEY_D] )
    {
        buttonD ->execute(deltaTime);
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
