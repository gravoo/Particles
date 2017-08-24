#pragma once
#include <MousePositionInGame.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>

class ICommand;
class InputHandler
{
public:
    InputHandler() = default;
    InputHandler(std::shared_ptr<ICommand> buttonUp,
                 std::shared_ptr<ICommand> buttonDown,
                 std::shared_ptr<ICommand> buttonLeft,
                 std::shared_ptr<ICommand> buttonRight,
                 std::shared_ptr<MousePositionInGame> mousePositionInGame);
    void handlePlayerInput();
    void setKeyboardKey(int key);
    void unsetKeyboardKey(int key);
    void setMouseKey(int key, GLfloat xpos, GLfloat ypos);
    void unsetMousedKey(int key);
    void setDeselectUnitCommand(std::shared_ptr<ICommand> rightClick);
    glm::vec2 getPositionInGame();
    void resetMouseKeyPressPositionInGame();

private:
    GLboolean keys[1024];
    GLboolean mouse[9];
    std::shared_ptr<ICommand> buttonW;
    std::shared_ptr<ICommand> buttonS;
    std::shared_ptr<ICommand> buttonA;
    std::shared_ptr<ICommand> buttonD;
    std::shared_ptr<MousePositionInGame> mousePositionInGame;
    std::shared_ptr<ICommand> rightMouseClick;
    glm::vec2 currentMousePosition;
};
