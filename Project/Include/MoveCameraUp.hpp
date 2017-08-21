#pragma once
#include<ICommand.hpp>
#include<Camera.hpp>
#include<memory>
class MoveCameraUp : public ICommand
{
public:
    MoveCameraUp(std::shared_ptr<Camera> camera) : camera(camera)
    {}
    void execute(GLfloat deltaTime) override
    {
        camera->ProcessKeyboard(Camera_Movement::UP, deltaTime);
    };
private:
    std::shared_ptr<Camera> camera;
};
