#pragma once
#include<MoveCameraUp.hpp>
#include<MoveCameraDown.hpp>
#include<MoveCameraLeft.hpp>
#include<MoveCameraRight.hpp>

class InputHandler
{
public:
    InputHandler(std::shared_ptr<ICommand> buttonUp,
                 std::shared_ptr<ICommand> buttonDown,
                 std::shared_ptr<ICommand> buttonLeft,
                 std::shared_ptr<ICommand> buttonRight);
    void handleMouseInput();
    void handleKeyboardInput(GLfloat deltaTime);
    void setKeyboardKey(int key);
    void unsetKeyboardKey(int key);
private:
    GLboolean keys[1024];
    std::shared_ptr<ICommand> buttonW;
    std::shared_ptr<ICommand> buttonS;
    std::shared_ptr<ICommand> buttonA;
    std::shared_ptr<ICommand> buttonD;

};
