#pragma once
#include<ICommand.hpp>
#include<Camera.hpp>
#include<memory>
class MoveCameraDown : public ICommand
{
public:
    MoveCameraDown(std::shared_ptr<Camera> camera) : camera(camera)
    {}
    void execute(GLfloat deltaTime) override
    {
        camera->ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
    };
private:
    std::shared_ptr<Camera> camera;
};

