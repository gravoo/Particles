#pragma once
#include<ICommand.hpp>
#include<Camera.hpp>
#include<memory>
class MoveCameraLeft : public ICommand
{
public:
    MoveCameraLeft(std::shared_ptr<Camera> camera) : camera(camera)
    {}
    void execute(GLfloat deltaTime) override
    {
        camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    };
private:
    std::shared_ptr<Camera> camera;
};


