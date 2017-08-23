#pragma once
#include<GameBuildUnit.hpp>
#include<GameLevel.hpp>
#include<InputHandler.hpp>

class Units
{
public:
    Units() = default;
    Units(InputHandler &inputHandler, GameLevel &gameLevel);
    void update(GLfloat deltaTime);
    void render();
private:
    InputHandler inputHandler;
    GameLevel gameLevel;
};
