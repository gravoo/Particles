#include <InputHandler.hpp>
#include <cassert>
InputHandler::InputHandler(std::shared_ptr<ICommand> buttonUp,
                 std::shared_ptr<ICommand> buttonDown,
                 std::shared_ptr<ICommand> buttonLeft,
                 std::shared_ptr<ICommand> buttonRight)
: buttonW(buttonUp), buttonS(buttonDown), buttonA(buttonLeft), buttonD(buttonRight)
{

}

void InputHandler::handleKeyboardInput()
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

}

void InputHandler::setKeyboardKey(int key)
{
    keys[key] = GL_TRUE;
}

void InputHandler::unsetKeyboardKey(int key)
{
    keys[key] = GL_FALSE;
}
